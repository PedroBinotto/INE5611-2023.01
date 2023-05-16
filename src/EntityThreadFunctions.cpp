#include "EntityThreadFunctions.hpp"

namespace EntityThreadFunctions {
namespace {
void handleMissleLaunch(utils::Types::GameState *state) { utils::log(std::to_string(state->playerPosition)); }
} // namespace

void *player(void *arg) {
  utils::Types::GameState *state = (utils::Types::GameState *)arg;
  utils::Types::Board &board = state->boardState;
  int &pos = state->playerPosition;

  const int INPUT_INTERVAL = 20000;
  int x, y;
  y = state->boardState.size();
  x = state->boardState[0].size();
  std::vector<int> &playerRow = board[y - 1];
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
      playerRow[pos] = 0;
      pos = newPos;
    }
    playerRow[pos] = utils::Types::EntityEnum::PLAYER;
    usleep(INPUT_INTERVAL);
  }
}

void *alien(void *arg) {
  utils::Types::AlienProps *props = (utils::Types::AlienProps *)arg;
  utils::Types::GameState *state = props->state;
  int id = props->id;
  delete props;

  utils::log("id " + std::to_string(id));
  return NULL;
}
} // namespace EntityThreadFunctions
