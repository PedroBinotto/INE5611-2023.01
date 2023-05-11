#include <sstream>

#include "Game.hpp"
#include "utils.hpp"

using namespace std;

void log_startup_inf(utils::Board &board, pair<int, int> termDimensions, pair<int, int> playableArea) {
  utils::log("term x dimension: " + to_string(termDimensions.first));
  utils::log("to scale: " + to_string(playableArea.first));
  utils::log("term y dimension: " + to_string(termDimensions.second));
  utils::log("to scale: " + to_string(playableArea.second));
  utils::log_board_state(board);
}

void *testThread(void *arg) {
  const void *address = static_cast<const void *>(arg);
  std::stringstream ss;
  ss << address;
  std::string name = ss.str();

  utils::Board board = *(utils::Board *)arg;
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      board[i][j] = utils::ENEMY;
      utils::log("GAME gamestate memory address: " + name);
      utils::log_board_state(board);
      sleep(3);
    }
  }

  return NULL;
}

Game::Game(void) : state(new utils::GameState), interface(InterfaceClient()) {
  interface.start();
  const pair<int, int> d = interface.getDimensions();
  const pair<int, int> a = interface.getPlayableArea();
  const int x = a.first;
  const int y = a.second;

  state->boardState = std::vector<std::vector<int>>(y, std::vector<int>(x));
  log_startup_inf(state->boardState, d, a);
  startGameThreads();
  // state->boardState[state->boardState.size() - 1][state->boardState[0].size() / 2] = utils::PLAYER;
}

Game::~Game(void) {
  interface.stop();
  delete state;
}

void Game::draw() { interface.update(state); }

void Game::startGameThreads(void) {
  pthread_t thread;
  pthread_create(&thread, NULL, testThread, &state->boardState);
}
