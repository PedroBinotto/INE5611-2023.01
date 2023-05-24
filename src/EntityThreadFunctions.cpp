#include "EntityThreadFunctions.hpp"
#include "utils.hpp"
#include <cmath>
#include <pthread.h>
#include <string>
#include <utility>

namespace EntityThreadFunctions {
  namespace Sync {
    void writerEnterCSection(utils::Types::CriticalResource *resource) {
      sem_wait(&resource->writerSem);
      resource->writeCount++;
      if (resource->writeCount == 1)
        sem_wait(&resource->readTrySem);
      sem_post(&resource->writerSem);
      sem_wait(&resource->resourceSem);
    }

    void writerExitCSection(utils::Types::CriticalResource *resource) {
      sem_post(&resource->resourceSem);
      sem_wait(&resource->writerSem);
      resource->writeCount--;
      if (resource->writeCount == 0)
        sem_post(&resource->readTrySem);
      sem_post(&resource->writerSem);
    }

    void autoWriteCSection(utils::Types::CriticalResource *resource, std::function<void(void)> op) {
      writerEnterCSection(resource);
      op();
      writerExitCSection(resource);
    }

    utils::Types::CriticalResource readerEnterCSection(utils::Types::CriticalResource *resource) {
      sem_wait(&resource->readTrySem);
      sem_wait(&resource->readerSem);
      resource->readCount++;
      if (resource->readCount == 1)
        sem_wait(&resource->resourceSem);
      sem_post(&resource->readerSem);
      sem_post(&resource->readTrySem);
      return *resource;
    }

    void readerExitCSection(utils::Types::CriticalResource *resource) {
      sem_wait(&resource->readerSem);
      resource->readCount--;
      if (resource->readCount == 0)
        sem_post(&resource->resourceSem);
      sem_post(&resource->readerSem);
    }

    void autoReadCSection(utils::Types::CriticalResource *resource,
                          std::function<void(utils::Types::CriticalResource resource)> op) {
      op(readerEnterCSection(resource));
      readerExitCSection(resource);
    }
  } // namespace Sync
  namespace {
    void handleMissleLaunch(utils::Types::MissileProps *props) {
      pthread_t thread;
      pthread_create(&thread, NULL, missile, props);
    }
  }                         // namespace
  void *player(void *arg) { // TODO: quem sabe usar mutex aqui mas sinceramente fodase nao tem diferenca
    utils::Types::GameState *state = (utils::Types::GameState *)arg;
    utils::Types::Board &board = state->boardState;
    int &pos = state->playerPosition;

    int x, y;
    y = state->boardState.size();
    x = state->boardState[0].size();
    std::vector<utils::Types::Element *> &playerRow = board[y - 1];
    pos = x / 2;

    while (true) {
      int ch;
      int newPos;
      if ((ch = getch()) != ERR) {
        if (ch >= 'A' && ch <= 'Z')
          ch += 32;
        switch (ch) {
        case 'd':
          newPos = pos + 1;
          break;
        case 'a':
          newPos = pos - 1;
          break;
        case ' ':
          utils::Types::MissileProps *props = new utils::Types::MissileProps;
          props->state = state;
          props->playerPosX = pos;
          handleMissleLaunch(props);
        }
      }
      if (newPos != pos && newPos > 0 && newPos < x) {
        playerRow[pos]->displayValue = 0;
        pos = newPos;
      }
      playerRow[pos]->displayValue = utils::Types::EntityEnum::PLAYER;
      usleep(utils::INPUT_INTERVAL);
    }
  }

  void *alien(void *arg) {
    int id;
    utils::Types::GameState *state;
    utils::Types::Alien *self;
    std::pair<int, int> area;

    utils::Types::AlienProps *props = (utils::Types::AlienProps *)arg;

    state = props->state;
    id = props->id;
    self = state->aliens[id];
    area = props->playableArea;
    bool alive = true;
    auto maxY = area.first;

    delete props;

    while (true) {
      auto pos = self->pos;
      auto &board = state->boardState;
      auto x = pos.first;
      auto y = pos.second;

      Sync::autoWriteCSection(board[x][y], [&state, &self, &alive, &y, x, maxY, id]() {
        state->boardState[x][y]->displayValue = 0;
        Sync::autoWriteCSection(self, [&state, &self, &alive, &y, x, maxY, id]() {
          alive = self->alive;
          if (!alive)
            return;
          auto nextY = (y + 1) % maxY;
          Sync::autoWriteCSection(state->boardState[x][nextY], [&state, &self, x, y, nextY, id]() {
            if (state->boardState[x][nextY]->displayValue == 0) {
              state->boardState[x][nextY]->displayValue = utils::Types::EntityEnum::ENEMY;
              state->boardState[x][nextY]->entityId = id;
              state->boardState[x][y]->entityId = 0;
              self->pos = {x, nextY};
              return;
            }
            state->boardState[x][nextY]->displayValue = 0;
            state->boardState[x][nextY]->entityId = 0;
            state->boardState[x][y]->displayValue = utils::Types::EntityEnum::ENEMY;
          });
        });
      });
      usleep(utils::ENEMY_MOV_SPEED_FACT / state->difficulty);
      if (!alive)
        break;
    }

    return NULL;
  }

  void *missile(void *arg) {
    utils::Types::MissileProps *props = (utils::Types::MissileProps *)arg;
    utils::Types::GameState *state = props->state;
    std::pair<int, int> initialPos = {state->boardState.size() - 2, props->playerPosX};
    int prev;

    delete props;

    for (int i = initialPos.first; i >= 0; i--) {
      bool hit = false;

      Sync::autoWriteCSection(state->boardState[prev][initialPos.second], [&state, prev, initialPos]() {
        if (prev)
          state->boardState[prev][initialPos.second]->displayValue = 0;
      });
      Sync::autoWriteCSection(state->boardState[i][initialPos.second], [&state, &hit, i, initialPos]() {
        if (state->boardState[i][initialPos.second]->displayValue == 2) {
          auto alien = state->aliens[state->boardState[i][initialPos.second]->entityId];
          Sync::autoWriteCSection(alien, [&alien]() { alien->alive = false; });
          hit = true;
        }
        state->boardState[i][initialPos.second]->displayValue = 3;
        hit = false;
      });
      if (hit)
        break;
      prev = i;
      usleep(utils::MISSILE_MOV_SPEED_FACT);
    }
    state->boardState[prev][initialPos.second]->displayValue = 0;

    return NULL;
  }

  void *missileGenerator(void *arg) {}

  void *timer(void *arg) {
    utils::Types::GameState *state = (utils::Types::GameState *)arg;
    int timePast = 0;

    while (true) {
      int won = 1;
      for (auto alien : state->aliens) {
        if (alien->alive)
          won = 0;
      }
      if (timePast >= utils::TIME_LIMIT)
        won = -1;
      state->over = won;
      if (state->over != 0)
        break;
      timePast++;
      state->timePast = timePast;
      sleep(1);
    }

    return NULL;
  }
} // namespace EntityThreadFunctions
