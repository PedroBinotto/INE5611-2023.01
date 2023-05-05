#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <fstream>
#include <iostream>
#include <mutex>

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
