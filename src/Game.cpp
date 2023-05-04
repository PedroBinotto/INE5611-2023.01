#include <exception>
#include <iostream>
#include <math.h>

#include "Game.hpp"

Game::Game(void) : state(0), interfaceClient(InterfaceClient()) {
  interfaceClient.start();
}

Game::~Game(void) { interfaceClient.stop(); }

void Game::update() { state++; }

void Game::draw() {
  interfaceClient.draw(&state);
  interfaceClient.ref();
}
