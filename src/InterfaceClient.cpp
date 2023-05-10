#include "InterfaceClient.hpp"

using namespace std;

string getSprite(int e) {
  switch (e) {
  case utils::ENEMY:
    return "\n/WwW\\\n"
           " V V\n";
    break;
  case utils::PLAYER:
    return "\n^\n"
           "^\n";
    break;
  case utils::MISSILE:
    return "\n0\n";
    break;
  default:
    return "";
  }
}

InterfaceClient::InterfaceClient(void) {}

void InterfaceClient::start(void) {
  initscr();
  curs_set(false);
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_GREEN, COLOR_RED);
  utils::log(getSprite(utils::ENEMY));
  utils::log(getSprite(utils::ENEMY));
}

void InterfaceClient::update(utils::GameState &state) {
  clear();
  draw(state);
  refresh();
}

std::pair<int, int> InterfaceClient::getDimensions(void) {
  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);

  return {maxY, maxX};
}

std::pair<int, int>
InterfaceClient::virtualPositionToCoordinates(std::pair<int, int> pos,
                                              bool reverse = false) {
  return {1, 2};
}

void InterfaceClient::draw(utils::GameState &state) {
  for (int i = 0; i < state.boardState.size(); i++) {
    for (int j = 0; j < state.boardState[i].size(); j++) {
      auto coords = virtualPositionToCoordinates({i, j});
      mvprintw(coords.second, coords.first,
               getSprite(state.boardState[i][j]).c_str());
    }
  }
}

void InterfaceClient::stop(void) { endwin(); }
