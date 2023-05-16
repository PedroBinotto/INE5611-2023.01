#include <ncurses.h>
#include <unistd.h>

#include "utils.hpp"

namespace EntityThreadFunctions {
void *player(void *arg);
void *missile(void *arg);
void *alien(void *arg);
} // namespace EntityThreadFunctions
