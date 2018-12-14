#include "graph_handler.hpp"

namespace game {

class game_state {
  enum state {
    GM_START = 0,
    GM_PAUSED =  1,
    GM_PLAY = 2 ,
    GM_EXIT = 3
  };
};

class game : game_state {
public:
  game() {}
  virtual ~game(){};

  void game_handler();
  int main_menu(int in);
  int run();
  int init();

private:
  bool running;
  graphics handler;
};

} // namespace game
