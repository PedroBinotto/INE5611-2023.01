#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "Logger.hpp"
#include "utils.hpp"

const string LOGDIR = "log/";

Logger *Logger::pinstance_{nullptr};
std::mutex Logger::mutex_;

Logger::Logger(void) {
  auto epoch =
      to_string(std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count());
  utils::create_directory(LOGDIR);
  string file = LOGDIR + epoch + "_log.txt";
  logfile = std::ofstream(file);
}

Logger *Logger::getInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new Logger();
  }
  return pinstance_;
}

Logger::~Logger(void) { logfile.close(); }

void Logger::log(const std::string &msg) { logfile << msg << endl; }
