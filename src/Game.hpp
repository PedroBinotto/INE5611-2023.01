#ifndef __GAME_H__
#define __GAME_H__

#include <exception>
#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <pthread.h>
#include <string>
#include <utility>
#include <vector>

#include "InterfaceClient.hpp"
#include "utils.hpp"

class Game {
  utils::GameState *state;
  InterfaceClient interface;

public:
  Game(void);
  ~Game(void);

  void draw(void);
};

#endif
