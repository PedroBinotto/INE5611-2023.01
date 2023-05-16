#ifndef __GAME_H__
#define __GAME_H__

#include <exception>
#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "EntityThreadFunctions.hpp"
#include "InterfaceClient.hpp"
#include "utils.hpp"

class Game {
  utils::GameState *state;
  InterfaceClient interface;

  void startGameThreads(void);

public:
  Game(void);
  ~Game(void);

  void draw(void);
};

#endif
