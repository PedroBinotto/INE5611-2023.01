#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <utility>

#include "InterfaceClient.hpp"
#include "Logger.hpp"

using namespace std;

InterfaceClient::InterfaceClient(void) : _board(0) {}

pair<int, int> InterfaceClient::start(void) {
  Logger *logger = Logger::getInstance();
  int maxX, maxY;
  initscr();
  curs_set(false);
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_GREEN, COLOR_RED);
  getmaxyx(stdscr, maxY, maxX);
  logger->log("max X: ");
  logger->log(to_string(maxX));
  logger->log("max Y: ");
  logger->log(to_string(maxY));
  return {maxX, maxY};
}

void InterfaceClient::setBoard(long state) { _board = state; }

void InterfaceClient::draw(void) { mvprintw(0, _board, "o"); }

void InterfaceClient::ref(void) {
  clear();
  draw();
  refresh();
}

void InterfaceClient::stop(void) { endwin(); }
