#ifndef __UTILS_H__
#define __UTILS_H__

#include <chrono>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace utils {
namespace Types {
struct Element {
  int value;
  int readcount = 0;
  pthread_mutex_t writerMutex;
  sem_t readerSemaphore;
};

typedef std::vector<std::vector<Element *>> Board;

enum EntityEnum { PLAYER = 1, ENEMY = 2, MISSILE = 3 };

struct Alien {
  int id;
  std::pair<int, int> pos;
  bool alive;
};

struct GameState {
  Board boardState;
  std::vector<Alien *> aliens;
  int playerPosition;
};

struct AlienProps {
  GameState *state;
  int id;
};
} // namespace Types

std::string currentUnixTime(void);
void create_directory(const std::string &path);
void log(const std::string &msg);
void logStartupInf(Types::Board &board, std::pair<int, int> termDimensions, std::pair<int, int> playableArea);
void logBoardState(Types::Board &board);

const int ENEMY_ROWS = 2;
const int ENEMIES_PER_ROW = 10;
const int ENEMY_SPACING = 5;
const int MIN_X = (ENEMIES_PER_ROW * ENEMY_SPACING) + 1;
const int MIN_Y = 5;
} // namespace utils

#endif
