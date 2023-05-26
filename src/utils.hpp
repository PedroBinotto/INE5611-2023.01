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
      int displayValue = 0;
      int entityId = 0;
    };

    struct Alien : CriticalResource {
      int id = 0;
      std::pair<int, int> pos = {0, 0};
      bool alive = true;
    };

    struct MissileBattery : CriticalResource {
      int n = 6;
    };

    typedef std::vector<std::vector<Element *>> Board;

    enum EntityEnum { PLAYER = 1, ENEMY = 2, MISSILE = 3 };

    struct GameState {
      Board boardState;
      std::vector<Alien *> aliens;
      MissileBattery *battery;
      int playerPosition;
      int difficulty;
      int timePast;
      int over;
    };

    struct AlienProps {
      GameState *state;
      std::pair<int, int> playableArea;
      int id;
    };

    struct MissileProps {
      GameState *state;
      int playerPosX;
    };
  } // namespace Types

  std::string currentUnixTime(void);
  void create_directory(const std::string &path);
  void log(const std::string &msg);
  void logStartupInf(Types::Board &board, std::pair<int, int> termDimensions, std::pair<int, int> playableArea);
  void logBoardState(Types::Board &board);
  void logAliens(Types::GameState *state);

  const int ENEMY_ROWS = 4;
  const int ENEMIES_PER_ROW = 5;
  const int ENEMY_SPACING = 6;
  const int ENEMY_MOV_SPEED_FACT = 100000;
  const int MISSILE_MOV_SPEED_FACT = 62500;
  const int MAX_MISSILE_CAPACITY = 6;
  const int MISSILE_GENERATOR_INTERVAL = 1; // SECS
  const int INPUT_INTERVAL = 20000;         // USECS
  const int TIME_LIMIT = 90;                // SECS
  const int FR = 33;
  const int FR_MODIFIER = 1000;
  const int SCALE = 3;
  const int MIN_X = (ENEMIES_PER_ROW * ENEMY_SPACING) + 1;
  const int MIN_Y = 5;
  const int TIMER_POS = 3; // 0 TOP LEFT ; 1 TOP RIGHT ; 2  BOTTOM LEFT ; 3 BOTTOM RIGHT
  const int AMMO_COUNTER_POS = 0;
} // namespace utils

#endif
