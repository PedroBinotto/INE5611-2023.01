#include "EntityThreadFunctions.hpp"

namespace EntityThreadFunctions {
namespace {
void handleMissleLaunch(utils::Types::GameState *state) { utils::log(std::to_string(state->playerPosition)); }
} // namespace

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
      }
    }
    if (newPos != pos && newPos > 0 && newPos < x) {
      playerRow[pos]->value = 0;
      pos = newPos;
    }
    playerRow[pos]->value = utils::Types::EntityEnum::PLAYER;
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

  delete props;

  while (true) { // TODO: mutex
    auto pos = self->pos;
    state->boardState[pos.first][pos.second]->value = 0;

    if (!self->alive)
      break;

    std::pair<int, int> newPos = {pos.first, (pos.second + 1) % area.first};
    state->aliens[id]->pos = {pos.first, newPos.second};
    state->boardState[newPos.first][newPos.second]->value = utils::Types::EntityEnum::ENEMY;

    usleep(utils::ENEMY_MOV_SPEED_FACT / state->difficulty);
  }

  return NULL;
}
} // namespace EntityThreadFunctions
