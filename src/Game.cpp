#include "Game.hpp"
#include "utils.hpp"

using namespace std;

void logBoardState(utils::Board &board) {
  for (int i = 0; i < board.size(); i++) {
    string out = "[ ";
    for (int j = 0; j < board[i].size(); j++) {
      board[i][j] = (i % 2 == 0) && i < 3 ? utils::ENEMY : i < 3 ? utils::PLAYER : 0;
      out += to_string(board[i][j]) + " ";
    }
    out += "]";
    utils::log(out);
  }
}

Game::Game(void) : state(new utils::GameState), interface(InterfaceClient()) {
  interface.start();
  const pair<int, int> d = interface.getDimensions();
  const pair<int, int> a = interface.getPlayableArea();
  const int x = a.first;
  const int y = a.second;

  state->boardState = std::vector<std::vector<int>>(y, std::vector<int>(x));

  utils::log("term x dimension: " + to_string(d.first));
  utils::log("to scale: " + to_string(x));
  utils::log("term y dimension: " + to_string(d.second));
  utils::log("to scale: " + to_string(y));

  logBoardState(state->boardState);
  state->boardState[state->boardState.size() - 1][state->boardState[0].size() / 2] = utils::PLAYER;
}

Game::~Game(void) {
  interface.stop();
  delete state;
}

void Game::draw() { interface.update(*state); }
