#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

namespace game {

class game {
public:
  game() {}
  virtual ~game(){};

  void game_handler();
  int main_menu(int in);
  int init();
};

} // namespace game
