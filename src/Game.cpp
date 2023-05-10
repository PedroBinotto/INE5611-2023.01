#include "Game.hpp"

using namespace std;

Game::Game(void) : state(new utils::GameState), interface(InterfaceClient()) {
  interface.start();

  pair<int, int> d = interface.getDimensions();

  utils::log("term x dimension: " + to_string(d.first));
  utils::log("term y dimension: " + to_string(d.second));
}

Game::~Game(void) {
  interface.stop();
  delete state;
}

void Game::draw() { interface.update(*state); }
