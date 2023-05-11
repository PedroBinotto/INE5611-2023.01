#ifndef __UTILS_H__
#define __UTILS_H__

#include <chrono>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace utils {
void create_directory(const std::string &path);
void log(const std::string &msg);
std::string currentUnixTime(void);
typedef std::vector<std::vector<int>> Board;
enum EntityEnum { PLAYER = 1, ENEMY = 2, MISSILE = 3 };
void log_board_state(utils::Board &board);
struct GameState {
  utils::Board boardState;
  int playerPosition;
};
const int MIN_X = 212;
const int MIN_Y = 42;
} // namespace utils

#endif
