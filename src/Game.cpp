#include <exception>
#include <iostream>

#include "Game.hpp"

Game::Game(void) : state(0) {}

void Game::update() { state++; }

void Game::draw() { std::cout << state << std::endl; }
