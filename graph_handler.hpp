#include <SFML/Graphics.hpp>

namespace game {

class graphics {
public:
  graphics() {}

  void set_window(sf::RenderWindow *window);
  void display(); 

private:
  sf::RenderWindow *main_window;
};

} // namespace game
