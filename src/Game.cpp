#include <sstream>

#include "Game.hpp"

using namespace std;

Game::Game(void) : state(new utils::GameState), interface(InterfaceClient()) {
  interface.start();
  const pair<int, int> d = interface.getDimensions();
  const pair<int, int> a = interface.getPlayableArea();
  const int x = a.first;
  const int y = a.second;

  state->boardState = std::vector<std::vector<int>>(y, std::vector<int>(x));
  utils::logStartupInf(state->boardState, d, a);
  startGameThreads();
}

Game::~Game(void) {
  interface.stop();
  delete state;
}

void Game::draw() { interface.update(state); }

void Game::startGameThreads(void) {
  pthread_t thread;
  pthread_create(&thread, NULL, EntityThreadFunctions::player, state);
  // TODO: create alien threads ...
}
