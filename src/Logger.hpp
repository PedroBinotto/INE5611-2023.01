#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "utils.hpp"

using namespace std;

class Logger {
private:
  static Logger *pinstance_;
  static std::mutex mutex_;

protected:
  Logger(void);
  ~Logger(void);
  std::ofstream logfile;

public:
  Logger(Logger &other) = delete;
  void operator=(const Logger &) = delete;
  static Logger *getInstance();
  void log(const string &msg);
};

#endif
