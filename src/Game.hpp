#ifndef __GAME_H__
#define __GAME_H__

#include "InterfaceClient.hpp"

class Game {
  long state;
  InterfaceClient interface;
  void draw(void);

public:
  Game(void);
  ~Game(void);

  void update(void);
};

#endif
