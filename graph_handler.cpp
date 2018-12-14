#include "graph_handler.hpp"

namespace game {

void graphics::set_window(sf::RenderWindow *window) { main_window = window; }

void graphics::display() { main_window->display(); }

} // namespace game
