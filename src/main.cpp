#include <chrono>
#include <iostream>
#include <unistd.h>

#include "Game.hpp"

using namespace std;

const int MOD = 1000;

int main(void) {
  Game game = Game();

  auto now = chrono::system_clock::now();
  auto lastFrame = chrono::system_clock::now();

  while (true) {
    now = chrono::system_clock::now();
    int delta = (now - lastFrame).count() / MOD;
    lastFrame = now;

    if (delta < (33 * MOD)) {
      usleep((33 * MOD) - delta);
    }

    game.update();
    game.draw();
  }

  return 0;
}
