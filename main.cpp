#include<iostream>
#include <list>

#include <SFML/Graphics.hpp>

#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

class Object {
    public:
        std::pair<int, int> pos;        
};

class Buttons {
    public:
        std::list<Object> btns;
        Buttons() {
            init_pos();
        }

        void init_pos() {
            int x = 100;
            int y = 25;
            for (int i=0; i < buttons; i++, y+=25) {
                Object obj;
                obj.pos = std::make_pair(x,y);
                btns.emplace_back(obj);
            }
        }

    private:
        int buttons = 3;
        sf::RectangleShape but;
};
class Balls{
    public:
        std::list<Object> balls;
        Balls() {
            init_pos();

        }

        void init_pos() {
            for (int i=0; i < nballs; ++i) {
                Object obj;
                obj.pos = std::make_pair(0,0);
                balls.emplace_back(obj);
            }
        }

    private:
        int nballs = 50;
        sf::CircleShape ball;
};

class Game {
    public:
        int crdts;
        int state;
        Balls gm_object = Balls();

        Game() {
            crdts = 0;        
            state = GM_START;
        }

        void game_handler() {
            std::cout << "game" << std::endl;

            for(auto obj: gm_object.balls)
                std::cout << obj.pos.first << std::endl;

        }

        void add_credits() {
            crdts++;
        }

        void main_menu() {
            bool input = false;
            int opt = 0;

            //0 = add credits
            //1 = play game
            //2 = exit
            while (!input) {
                std::cin >> opt;

                if (std::cin.fail())
                    continue;

                switch(opt) {
                    case 0:
                        add_credits();
                        input = true;
                        break;
                    case 1:
                        state = GM_PLAY;
                        input = true;
                        break;
                    case 2:
                        state = GM_EXIT;
                        input = true;
                        break;
                    default:
                        continue;
                }            
            }
        }
};

void draw_all(Balls balls, Buttons btns, sf::RenderWindow* window) {
        window->display();
}

int main() {

    Game loop = Game();
    Buttons btns = Buttons();
    sf::RenderWindow window(sf::VideoMode(200, 200), "fmq_game");

    while (loop.state != GM_EXIT) {
        std::cout << loop.state << std::endl;
        switch(loop.state) {
            case GM_START:
                loop.main_menu();
                break;
            case GM_PLAY:
                loop.game_handler();
                break;
        }
        draw_all(loop.gm_object, btns, &window);
    }
}
