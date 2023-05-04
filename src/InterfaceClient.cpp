#include <curses.h>
#include <iostream>
#include <ncurses.h>

#include "InterfaceClient.hpp"

using namespace std;

InterfaceClient::InterfaceClient(void) {}

void InterfaceClient::draw(void *arg) { printw("Hello, World!"); }

void InterfaceClient::start(void) { initscr(); }

void InterfaceClient::ref(void) { refresh(); }

void InterfaceClient::stop(void) { endwin(); }
