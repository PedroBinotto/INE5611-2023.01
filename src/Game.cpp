#include "Game.hpp"

using namespace std;

Game::Game(void) : state(new utils::Types::GameState), interface(InterfaceClient()) {
  interface.start();
  const pair<int, int> d = interface.getDimensions();
  const pair<int, int> a = interface.getPlayableArea();
  const int x = a.first;
  const int y = a.second;

  if (x < utils::MIN_X || y < utils::MIN_Y) {
    interface.stop();
    cout << "Terminal mto pequeno" << endl; // TODO: tratamenro definitivo
    exit(1);
  }

  state->boardState = std::vector<std::vector<int>>(y, std::vector<int>(x));
  state->aliens = std::vector<utils::Types::Alien *>(utils::ENEMY_ROWS * utils::ENEMIES_PER_ROW);
  utils::logStartupInf(state->boardState, d, a);
  startGameThreads();
}

Game::~Game(void) {
  interface.stop();
  for (auto alien : state->aliens) {
    delete alien;
  }
  delete state;
}

void Game::draw() { interface.update(state); }

void Game::startGameThreads(void) {
  pthread_t playerThread;
  pthread_create(&playerThread, NULL, EntityThreadFunctions::player, state);

  int cnt = 0;
  const int rowSpan = (utils::ENEMIES_PER_ROW * utils::ENEMY_SPACING) - 1;
  const int initialPosRowPadding = (interface.getPlayableArea().first - rowSpan) / 2;
  for (int i = 0; i < utils::ENEMY_ROWS; i++) {
    for (int j = 0; j < utils::ENEMIES_PER_ROW; j++) {
      const int horizontalPos = (j * utils::ENEMY_SPACING) + initialPosRowPadding;

      state->aliens[cnt] = new utils::Types::Alien;
      utils::Types::Alien *alien = state->aliens[cnt];

      alien->id = cnt;
      alien->pos = {i, horizontalPos};
      alien->alive = true;
      state->boardState[i][horizontalPos + (i % utils::ENEMY_SPACING)] = utils::Types::EntityEnum::ENEMY;

      utils::Types::AlienProps *props = new utils::Types::AlienProps;
      props->state = state;
      props->id = cnt;

      pthread_t thread;
      pthread_create(&thread, NULL, EntityThreadFunctions::alien, props);

      cnt++;
    }
  }

  for (auto alien : state->aliens) {
    utils::log("alien " + to_string(alien->id) + " pos: " + to_string(alien->pos.second));
  }
}
