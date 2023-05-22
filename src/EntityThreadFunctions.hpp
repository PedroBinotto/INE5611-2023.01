#include <cmath>
#include <functional>
#include <ncurses.h>
#include <semaphore.h>
#include <unistd.h>

#include "utils.hpp"

namespace EntityThreadFunctions {
  namespace Sync {
    void writerEnterCSection(utils::Types::CriticalResource *resource);
    void writerExitCSection(utils::Types::CriticalResource *resource);
    void autoWriteCSection(utils::Types::CriticalResource *resource, std::function<void()> op);

    utils::Types::CriticalResource readerEnterCSection(utils::Types::CriticalResource *resource);
    void readerExitCSection(utils::Types::CriticalResource *resource);
    void autoReadCSection(utils::Types::CriticalResource *resource,
                          std::function<void(utils::Types::CriticalResource resource)> op);
  } // namespace Sync
  void *player(void *arg);
  void *missile(void *arg);
  void *alien(void *arg);
  void *timer(void *arg);
  void *missileGenerator(void *arg);
} // namespace EntityThreadFunctions
