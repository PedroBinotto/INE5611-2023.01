#include <exception>
#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <string>

#include "Game.hpp"

using namespace std;

Game::Game(void) : state(0), interface(InterfaceClient()) {
  const pair<int, int> termDimensions = interface.start();
}

Game::~Game(void) { interface.stop(); }

void Game::draw() {
  interface.setBoard(state);
  interface.ref();
}

void Game::update() {
  state++;
  draw();
}
