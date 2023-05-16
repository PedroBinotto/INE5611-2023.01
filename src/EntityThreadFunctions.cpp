#include "EntityThreadFunctions.hpp"
#include "utils.hpp"
#include <cmath>

const std::string LOGTAG = "[getch] ";

namespace EntityThreadFunctions {
namespace {
void handleMissleLaunch(utils::GameState *state) {}
} // namespace

void *player(void *arg) {

  utils::GameState *state = (utils::GameState *)arg;
  utils::Board &board = state->boardState;
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
    playerRow[pos] = utils::EntityEnum::PLAYER;
    usleep(INPUT_INTERVAL);
  }
}
} // namespace EntityThreadFunctions
