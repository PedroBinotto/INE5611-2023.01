#include "EntityThreadFunctions.hpp"

namespace EntityThreadFunctions {
  namespace Sync {
    template <typename T> void writerEnterCSection(T *criticalResource) {
      sem_wait(&criticalResource->writerSem);
      criticalResource->writeCount++;
      if (criticalResource->writeCount == 1)
        sem_wait(&criticalResource->readTrySem);
      sem_post(&criticalResource->writerSem);
      sem_wait(&criticalResource->resourceSem);
    }

    template <typename T> void writerExitCSection(T *criticalResource) {
      sem_post(&criticalResource->resourceSem);
      sem_wait(&criticalResource->writerSem);
      criticalResource->writeCount--;
      if (criticalResource->writeCount == 0)
        sem_post(&criticalResource->readTrySem);
      sem_post(&criticalResource->writerSem);
    }

    template <typename T> void autoWriteCSection(T *criticalResource, std::function<void(void)> op) {
      writerEnterCSection(criticalResource);
      op();
      writerExitCSection(criticalResource);
    }
  } // namespace Sync
  namespace {
    void handleMissleLaunch(utils::Types::GameState *state) { utils::log(std::to_string(state->playerPosition)); }
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
          handleMissleLaunch(state);
          utils::logAliens(state);
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

      Sync::writerEnterCSection(board[x][y]);
      auto el = state->boardState[x][y];
      el->displayValue = 0;
      Sync::writerEnterCSection(self);
      if (!self->alive) {
        alive = false;
      } else {
        auto newY = (y + 1) % maxY;
        Sync::writerEnterCSection(state->boardState[x][newY]);
        state->boardState[x][newY]->displayValue = utils::Types::EntityEnum::ENEMY;
        state->boardState[x][newY]->displayValue = utils::Types::EntityEnum::ENEMY;
        state->aliens[id]->pos = {x, newY};
        Sync::writerExitCSection(state->boardState[x][newY]);
      }
      Sync::writerExitCSection(self);
      Sync::writerExitCSection(board[x][y]);
      usleep(utils::ENEMY_MOV_SPEED_FACT / state->difficulty);
      if (!alive)
        break;
    }

    return NULL;
  }

  void *missile(void *arg) {}
} // namespace EntityThreadFunctions
