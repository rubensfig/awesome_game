#include <SFML/Graphics.hpp>

namespace game {

class graphics {
public:
  graphics() {}

  void get_window(sf::RenderWindow *window);
  void display() { main_window->display(); }

private:
  sf::RenderWindow *main_window;
};

} // namespace game
