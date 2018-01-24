#include<iostream>
#include <list>

#include <SFML/Graphics.hpp>

#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

class Object {
    public:
        std::pair<float, float> pos;        
};

class Buttons {
    public:
        std::list<Object> btns;
        Buttons() {
            init_pos();
        }

        void init_pos() {
            float x = 100;
            float y = 25;
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
        std::list<std::pair<sf::CircleShape, Object>> balls;

        virtual ~Balls() {};
        Balls() {
            for (int i=0; i < nballs; ++i) {
                Object obj;
                sf::CircleShape shape(30.f);
                shape.setFillColor(sf::Color::Green);
                shape.setPosition(30, 30);

                obj.pos = std::make_pair(0,0);

                balls.emplace_back(std::make_pair(shape, obj));
            }
            update_pos();
        }

        void update_pos() {
            std::pair<float, float> temp;
            for (auto &i : balls){

                float x = std::rand() % 900;
                float y = std::rand() % 730;

                i.second.pos.first = x;
                i.second.pos.second = y;
            }
        }
    private:
        int nballs = 50;
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

        virtual ~Game() {};

        void game_handler(const std::pair<float, float>* key_press) {
            //std::cout << "game" << std::endl
            gm_object.update_pos();

            auto element = find_closest(key_press);

            return;
        }

        std::pair<sf::CircleShape, Object> find_closest(const std::pair<float, float>* key_press) {
            int i = 0;
            for (auto b: gm_object.balls) {
                if(b.first.getGlobalBounds().contains(key_press->first, key_press->second)) {
                    return b;
                }
            }
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

void draw_all(Balls* balls, Buttons* btns, sf::RenderWindow* window) {
        
    window->clear();

    for (auto &it: balls->balls) {
        it.first.setPosition(it.second.pos.first, it.second.pos.second);
        window->draw(it.first);
    }

    window->display();
}

int main() {

    Game loop = Game();
    Buttons btns = Buttons();
    sf::RenderWindow window(sf::VideoMode(1024, 768), "fmq_game");
    sf::Event event;
    std::pair<float, float> key_press;
    bool pressed = false;

    while (loop.state != GM_EXIT) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left){
                    key_press = std::make_pair(event.mouseButton.x, event.mouseButton.y);
                    pressed = true;
                }
        }
        switch(loop.state) {
            case GM_START:
                loop.main_menu();
                break;
            case GM_PLAY:
                if (!pressed)
                    continue;

                loop.game_handler(&key_press);
                break;
        }
        draw_all(&loop.gm_object, &btns, &window);
        pressed = false;
    }
}
