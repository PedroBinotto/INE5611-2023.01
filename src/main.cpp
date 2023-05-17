#include <chrono>
#include <functional>
#include <unistd.h>

#include "Game.hpp"

using namespace std;

void mloop(function<void(void)> op);

const int MOD = 1000;
const int FR = 33;

int main(void) {
  int d;
  std::cout << "Selecione o nível de dificuldade entre:" << std::endl;
  std::cout << "1 - Fácil" << std::endl;
  std::cout << "2 - Médio" << std::endl;
  std::cout << "3 - Difícil" << std::endl;
  std::cin >> d;
  if (d <= 0 || d > 3) {
    std::cout << "Nível de dificuldade deve ser entre 1 e 3" << std::endl;
    exit(1);
  }
  Game game = Game(d);
  mloop([&game]() { game.draw(); });

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
