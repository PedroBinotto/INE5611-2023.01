#ifndef __GAME_H__
#define __GAME_H__

#include <exception>
#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <pthread.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "EntityThreadFunctions.hpp"
#include "InterfaceClient.hpp"
#include "utils.hpp"

class Game {
  utils::Types::GameState *state;
  InterfaceClient interface;

  void constructGameStructures(int x, int y);
  void startGameThreads(void);

public:
  Game(int dif);
  ~Game(void);

  void draw(void);
};

#endif
