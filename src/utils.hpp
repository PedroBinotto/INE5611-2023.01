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
struct CriticalResource {
  int readCount = 0;
  int writeCount = 0;
  sem_t readerSem, writerSem, readTrySem, resourceSem;
};

struct Element : CriticalResource {
  int displayValue;
  int entityId;
};

struct Alien : CriticalResource {
  int id;
  std::pair<int, int> pos;
  bool alive;
};

typedef std::vector<std::vector<Element *>> Board;

enum EntityEnum { PLAYER = 1, ENEMY = 2, MISSILE = 3 };

struct GameState {
  Board boardState;
  std::vector<Alien *> aliens;
  int playerPosition;
  int difficulty;
};

struct AlienProps {
  GameState *state;
  std::pair<int, int> playableArea;
  int id;
};
} // namespace Types

std::string currentUnixTime(void);
void create_directory(const std::string &path);
void log(const std::string &msg);
void logStartupInf(Types::Board &board, std::pair<int, int> termDimensions, std::pair<int, int> playableArea);
void logBoardState(Types::Board &board);
void logAliens(Types::GameState *state);

const int ENEMY_ROWS = 2;
const int ENEMIES_PER_ROW = 10;
const int ENEMY_SPACING = 5;
const int ENEMY_MOV_SPEED_FACT = 100000;
const int INPUT_INTERVAL = 20000;
const int FR = 33;
const int FR_MODIFIER = 1000;
const int SCALE = 3;
const int MIN_X = (ENEMIES_PER_ROW * ENEMY_SPACING) + 1;
const int MIN_Y = 5;
} // namespace utils

#endif
