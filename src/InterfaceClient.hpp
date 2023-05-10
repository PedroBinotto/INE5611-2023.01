#ifndef __ICLIENT_H__
#define __ICLIENT_H__

#include <curses.h>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <string>
#include <utility>

#include "utils.hpp"

class InterfaceClient {
  void draw(utils::GameState &state);
  std::pair<int, int> virtualPositionToCoordinates(std::pair<int, int> pos,
                                                   bool reverse);

public:
  InterfaceClient(void);

  void start(void);
  void stop(void);
  void update(utils::GameState &state);

  std::pair<int, int> getDimensions(void);
};

#endif
