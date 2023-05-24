#include "InterfaceClient.hpp"

using namespace std;

InterfaceClient::InterfaceClient(void) : SCALE(utils::SCALE), COLOR(has_colors()) {}

void InterfaceClient::start(void) {
  initscr();
  curs_set(false);
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, TRUE);
  use_default_colors();
  const pair<int, int> d = getDimensions();
  playableArea = {(d.first / (SCALE)), (d.second / (SCALE))};
  if (COLOR) {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
  }
}

void InterfaceClient::mainUpdate(utils::Types::GameState *state) {
  clear();
  draw(state);
  refresh();
}

std::pair<int, int> InterfaceClient::getDimensions(void) {
  int x, y;
  getmaxyx(stdscr, y, x);

  return {x, y};
}

int InterfaceClient::getScaleFactor(void) { return SCALE; }

std::pair<int, int> InterfaceClient::virtualPositionToTerminalCoordinates(std::pair<int, int> pos) {
  return {pos.first * SCALE, pos.second * SCALE};
}

pair<int, int> InterfaceClient::getPlayableArea(void) { return playableArea; }

vector<string> InterfaceClient::getSprite(int e) {
  switch (e) {
  case utils::Types::EntityEnum::ENEMY:
    return {"/W\\", "V-V", "   "};
    break;
  case utils::Types::EntityEnum::PLAYER:
    return {" ^ ", " ^ ", " ^ "};
    break;
  case utils::Types::EntityEnum::MISSILE:
    return {"   ", " 0 ", "   "};
    break;
  default:
    return {"   ", "   ", "   "};
  }
}

void InterfaceClient::printBlock(pair<int, int> &pos, vector<string> &sprite) {
  for (int i = 0; i < (int)sprite.size(); i++) {
    mvprintw(pos.second + i, pos.first, sprite[i].c_str());
  }
}

void InterfaceClient::printTimer(utils::Types::GameState *state) {
  map<int, std::pair<int, int>> positionMap{
      {0, {0, 0}},
      {1, {0, (playableArea.second - 2)}},
      {2, {playableArea.first - 1, 0}},
      {3, {playableArea.first - 1, playableArea.second - 2}},
  };
  pair<int, int> virtualPos = positionMap[utils::TIMER_POS];
  pair<int, int> pos = virtualPositionToTerminalCoordinates(virtualPos);

  ostringstream oss;
  oss << internal << setfill('0') << setw(SCALE) << (utils::TIME_LIMIT - state->timePast);
  string timeString = oss.str();
  vector<string> clockSprite = {"   ", timeString, "   "};

  printBlock(pos, clockSprite);
}

void InterfaceClient::printSprite(pair<int, int> pos, int entity) {
  vector<string> sprite = getSprite(entity);
  printBlock(pos, sprite);
}

void InterfaceClient::draw(utils::Types::GameState *state) {
  for (int i = 0; i < (int)state->boardState.size(); i++) {
    for (int j = 0; j < (int)state->boardState[i].size(); j++) {
      auto coords = virtualPositionToTerminalCoordinates({j, i});
      printSprite(coords, state->boardState[i][j]->displayValue);
    }
  }
  printTimer(state);
}

void InterfaceClient::stop(void) { endwin(); }
