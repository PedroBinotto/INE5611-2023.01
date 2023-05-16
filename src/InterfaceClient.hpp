#ifndef __ICLIENT_H__
#define __ICLIENT_H__

#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <utility>

#include "utils.hpp"

class InterfaceClient {
  const int SCALE;
  bool COLOR;
  std::pair<int, int> playableArea;

  void draw(utils::Types::GameState *state);
  void printSprite(std::pair<int, int> pos, int entity);
  std::vector<std::string> getSprite(int e);
  std::pair<int, int> virtualPositionToTerminalCoordinates(std::pair<int, int> pos);

public:
  InterfaceClient(void);

  void start(void);
  void stop(void);
  void update(utils::Types::GameState *state);

  std::pair<int, int> getDimensions(void);
  int getScaleFactor(void);
  std::pair<int, int> getPlayableArea(void);
};

#endif
