#include <assert.h>
#include <iostream>
#include <list>

#include "game.hpp"
#include "graph_handler.hpp"

int main() {

  game::game loop;
  game::graphics handler;

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  loop.init();
}
