#include "utils.hpp"

#include "Logger.hpp"
#include <semaphore.h>

namespace utils {
void create_directory(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    if (mkdir(path.c_str(), 0777) == 0)
      return;
  } else if (info.st_mode & S_IFDIR) {
    return;
  }
}

std::string currentUnixTime(void) {
  return std::to_string(
      std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void log(const std::string &msg) { Logger::getInstance()->log("[" + currentUnixTime() + "] " + msg); }

void logStartupInf(utils::Types::Board &board, pair<int, int> termDimensions, pair<int, int> playableArea) {
  utils::log("term x dimension: " + to_string(termDimensions.first));
  utils::log("to scale: " + to_string(playableArea.first));
  utils::log("term y dimension: " + to_string(termDimensions.second));
  utils::log("to scale: " + to_string(playableArea.second));
  utils::logBoardState(board);
}

void logBoardState(utils::Types::Board &board) {
  for (int i = 0; i < (int)board.size(); i++) {
    string out = "[ ";
    for (int j = 0; j < (int)board[i].size(); j++) {
      out += to_string(board[i][j]->value) + " ";
    }
    out += "]";
    utils::log(out);
  }
  utils::log("");
}

} // namespace utils
