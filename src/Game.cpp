#include "Game.hpp"

using namespace std;

Game::Game(int diff) : state(new utils::Types::GameState), interface(InterfaceClient()) {
  interface.start();
  state->difficulty = diff;
  const pair<int, int> d = interface.getDimensions();
  const pair<int, int> a = interface.getPlayableArea();
  const int x = a.first;
  const int y = a.second;

  checkMinimumDimensions(x, y);
  constructGameStructures(x, y);
  utils::logStartupInf(state->boardState, d, a);
  startGameThreads();
}

Game::~Game(void) {
  interface.stop();
  for (auto row : state->boardState) {
    for (auto element : row) {
      delete element;
    }
  }
  for (auto alien : state->aliens) {
    delete alien;
  }
  delete state;
}

void Game::draw() { interface.update(state); }

void Game::checkMinimumDimensions(int x, int y) {
  if (x < utils::MIN_X || y < utils::MIN_Y) {
    interface.stop();
    auto minxdef = utils::MIN_X * utils::SCALE;
    auto minydef = utils::MIN_Y * utils::SCALE;
    cout << "Seu terminal é muito pequeno para executar este programa. Definição mínima é de " << minxdef << " x "
         << minydef << "." << endl; // TODO: tratamenro definitivo
    exit(1);
  }
}

void Game::constructGameStructures(int x, int y) {
  state->boardState = std::vector<std::vector<utils::Types::Element *>>();
  state->aliens = std::vector<utils::Types::Alien *>(utils::ENEMY_ROWS * utils::ENEMIES_PER_ROW);

  for (int i = 0; i < y; i++) {
    state->boardState.push_back(vector<utils::Types::Element *>());
    for (int j = 0; j < x; j++) {
      utils::Types::Element *el = new utils::Types::Element;
      sem_init(&el->readerSem, 0, 1);
      sem_init(&el->writerSem, 0, 1);
      sem_init(&el->readTrySem, 0, 1);
      sem_init(&el->resourceSem, 0, 1);
      state->boardState[i].push_back(el);
    }
  }
}

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
      sem_init(&alien->resourceSem, 0, 1);
      sem_init(&alien->writerSem, 0, 1);
      sem_init(&alien->readTrySem, 0, 1);
      sem_init(&alien->resourceSem, 0, 1);

      alien->id = cnt;
      alien->pos = {i, horizontalPos};
      alien->alive = true;
      state->boardState[i][horizontalPos + (i % utils::ENEMY_SPACING)]->value = utils::Types::EntityEnum::ENEMY;

      utils::Types::AlienProps *props = new utils::Types::AlienProps;
      props->state = state;
      props->playableArea = interface.getPlayableArea(); // TODO: optimize
      props->id = cnt;

      pthread_t thread;
      pthread_create(&thread, NULL, EntityThreadFunctions::alien, props);

      cnt++;
    }
  }
}
