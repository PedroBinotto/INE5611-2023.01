#include "Logger.hpp"

const string LOGDIR = "log/";

Logger *Logger::pinstance_{nullptr};
std::mutex Logger::mutex_;

Logger::Logger(void) {
  auto epoch = utils::currentUnixTime();
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
