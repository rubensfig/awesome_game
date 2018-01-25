#include<iostream>
#include <list>
#include <assert.h>

#include <SFML/Graphics.hpp>

#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

class Object {
    public:
        std::pair<float, float> pos;

        Object (float x, float y) {
            pos = std::make_pair(x, y);
        }

        Object(std::pair<float, float> elem) {
            pos = elem;
        }

        bool operator() (const std::pair<sf::CircleShape, Object> pair) {
            return (pair.second.pos.first == pos.first && pair.second.pos.second == pos.second);
        }
};

class Buttons {
    public:
        std::list<std::tuple<sf::RectangleShape, Object, sf::Text>> btns;
        sf::Text t;
        std::string btn_color;

        bool visible;
        bool inter;

        Buttons(int nbuttons, bool interactive, std::string color, std::list<std::string> display_text) {
            buttons = nbuttons;
            visible = false;
            inter = interactive;
            btn_color = color;

            init_pos(display_text);
        }

        int input(std::pair<float, float>* keypress) {
            int i = 0;

            if (inter == false)
                return -1;
            
            for (auto b: btns) {
                if (std::get<0>(b).getGlobalBounds().contains(keypress->first, keypress->second)) {
                    std::cout << i << std::endl;
                    return i;
                }
                i++;
            }
            return -1;
        }

        void set_text(const std::string text) {
            t.setString(text);
        }


    private:
        int buttons;

        sf::Font font;

        void init_pos(std::list<std::string> display_text) {
            float x = 60;
            float y = 25;
            font.loadFromFile("arial.ttf");
            for (int i=0; i < buttons; i++, y+=40) {
                t = sf::Text(display_text.front(), font);
                display_text.pop_front();
                t.setCharacterSize(30);
                Object obj = Object(x, y);

                sf::RectangleShape shape;
                shape.setSize(sf::Vector2f(150, 30));

                if (btn_color == "Red")
                    shape.setFillColor(sf::Color::Red);
                if (btn_color == "Blue")
                    shape.setFillColor(sf::Color::Blue);

                btns.emplace_back(shape, obj, t);
            }
        }
};

class Balls{
    public:
        std::list<std::pair<sf::CircleShape, Object>> balls;

        virtual ~Balls() {};
        Balls() {
            for (int i=0; i < nballs; ++i) {
                sf::CircleShape shape(30.f);
                shape.setFillColor(sf::Color::Green);

                Object obj = Object(60, 30);

                balls.emplace_back(std::make_pair(shape, obj));
            }
            update_pos();
        }

        void update_pos() {
            std::pair<float, float> temp;
            for (auto &i : balls){

                float x = std::rand() % 870 + 90;
                float y = std::rand() % 700;

                i.second.pos.first = x;
                i.second.pos.second = y;
            }
        }

        void del_element(const std::pair<sf::CircleShape, Object>* rem_element) {
            Object rem = Object(rem_element->second.pos); 
            auto it = std::find_if(balls.begin(), balls.end(), rem);

            if (it != balls.end())
                balls.erase(it);
        }
    private:
        int nballs = 10;
};

class Game {
    public:
        int crdts;
        int state;
        int games;
        Balls gm_object = Balls();

        Game() {
            crdts = 0;        
            games = 0;
            state = GM_START;
        }

        virtual ~Game() {};

        void game_handler(const std::pair<float, float>* key_press) {
            //std::cout << "game" << std::endl;
            gm_object.update_pos();

            std::pair<sf::CircleShape, Object> element = find_closest(key_press);

            gm_object.del_element(&element);
            std::cout << "none" << std::endl;
            return;
        }

       std::pair<sf::CircleShape, Object> find_closest(const std::pair<float, float>* key_press) {
            int i = 0;
            for (auto b: gm_object.balls) {
                if(b.first.getGlobalBounds().contains(key_press->first, key_press->second)) {
                    return b;
                }
            }
            std::cout << "not found" << std::endl;
        }

        void add_credits() {
            crdts++;
        }

        void main_menu(int in) {
            int opt = 0;

            //0 = add credits
            //1 = play game
            //2 = pause game
            //3 = exit
            switch(in) {
                case 0:
                    add_credits();
                    break;
                case 1:
                    if (crdts <= 0)
                        break;

                    crdts--;

                    state = GM_PLAY;
                    break;
                case 2:
                    state = GM_PAUSED;
                    break;
                case 3:
                    state = GM_EXIT;
                    break;
                default:
                    return;
            }            
        }
};

void draw_all(Balls* balls, Buttons* btns, Buttons* counters, Buttons* games, sf::RenderWindow* window) {
        
    window->clear();

    for (auto &it: balls->balls) {
        it.first.setPosition(it.second.pos.first, it.second.pos.second);
        window->draw(it.first);
    }

    for (auto &it: btns->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first, pos.pos.second );
        txt->setPosition(pos.pos.first, pos.pos.second);

        window->draw(*rect);
        window->draw(*txt);
    }

    for (auto &it: counters->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first, pos.pos.second + 30*6 );
        txt->setPosition(pos.pos.first, pos.pos.second  + 30*6);

        window->draw(*rect);
        window->draw(*txt);
    }

    for (auto &it: games->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first, pos.pos.second + 35*7 );
        txt->setPosition(pos.pos.first, pos.pos.second  + 35*7);

        window->draw(*rect);
        window->draw(*txt);
    }

    window->display();
}

int main() {

    Game loop = Game();
        //Buttons(int nbuttons, bool interactive, string color) {
    Buttons move_btns = Buttons(4, true, "Red", {"add credits", "play", "pause", "exit"});
    Buttons counters = Buttons(1, false, "Blue", {""});
    Buttons games = Buttons(1, false, "Blue", {""});
    sf::RenderWindow window(sf::VideoMode(1024, 768), "fmq_game");
    sf::Event event;
    std::pair<float, float> key_press;
    bool pressed = false;

    draw_all(&loop.gm_object, &move_btns, &counters, &games, &window);
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
                if (!pressed)
                    continue;
                loop.main_menu(move_btns.input(&key_press));
                break;
            case GM_PAUSED:
                if (!pressed)
                    continue;
                loop.main_menu(move_btns.input(&key_press));
                break;
            case GM_PLAY:
                if (!pressed)
                    continue;

                loop.games++;
                loop.game_handler(&key_press);
                break;
        }

        std::get<2>(counters.btns.front()).setString(std::to_string(loop.crdts));
        std::get<2>(games.btns.front()).setString(std::to_string(loop.games));
        draw_all(&loop.gm_object, &move_btns, &counters, &games, &window);
        pressed = false;
    }
}
