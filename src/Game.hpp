#include "InterfaceClient.hpp"

class Game {
  long state;
  InterfaceClient interfaceClient;

public:
  Game(void);
  ~Game(void);

  void update(void);
  void draw(void);
};
