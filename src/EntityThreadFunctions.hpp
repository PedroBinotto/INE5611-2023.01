#include <cmath>
#include <functional>
#include <ncurses.h>
#include <semaphore.h>
#include <unistd.h>

#include "utils.hpp"

namespace EntityThreadFunctions {
namespace Sync {
template <typename T> void writeCSection(T *criticalResource, std::function<void()> op);
} // namespace Sync
void *player(void *arg);
void *missile(void *arg);
void *alien(void *arg);
} // namespace EntityThreadFunctions
