#include <chrono>
#include <functional>
#include <unistd.h>

#include "Game.hpp"

using namespace std;

void mloop(function<void(void)> op);

const int MOD = 1000;
const int FR = 33;

int main(void) {
  Game game = Game();
  mloop([&game]() { game.update(); });

  return 0;
}

void mloop(function<void(void)> op) {
  auto now = chrono::system_clock::now();
  auto lastFrame = chrono::system_clock::now();

  while (true) {
    now = chrono::system_clock::now();
    const int delta = (now - lastFrame).count() / MOD;
    lastFrame = now;

    if (delta < (FR * MOD)) {
      usleep((FR * MOD) - delta);
    }

    op();
  }
}
