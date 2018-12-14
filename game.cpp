#include "game.hpp"

namespace game {

int game::init() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  handler.set_window(&window);

  return 0;
}

int game::run() { 
  
  while(true)
    handler.display();

  return 0;
}

} // namespace game
