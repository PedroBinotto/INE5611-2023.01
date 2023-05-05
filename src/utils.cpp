#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <sys/stat.h>

#include "utils.hpp"

void utils::create_directory(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    if (mkdir(path.c_str(), 0777) == 0)
      return;
  } else if (info.st_mode & S_IFDIR) {
    return;
  }
}

#endif
