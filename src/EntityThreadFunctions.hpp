#include <cmath>
#include <functional>
#include <ncurses.h>
#include <semaphore.h>
#include <unistd.h>

#include "utils.hpp"

namespace EntityThreadFunctions {
  namespace Sync {
    template <typename T> void writerEnterCSection(T *criticalResource);
    template <typename T> void writerExitCSection(T *criticalResource);
    template <typename T> void autoWriteCSection(T *criticalResource, std::function<void()> op);
  } // namespace Sync
  void *player(void *arg);
  void *missile(void *arg);
  void *alien(void *arg);
  void *timer(void *arg);
  void *missileGenerator(void *arg);
} // namespace EntityThreadFunctions
