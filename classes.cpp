#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

class Symbol {
    public:
        std::pair<sf::Image, std::string> piece;

        Symbol (std::string filename) {
            sf::Image temp;
            temp.loadFromFile(filename);
            piece = std::make_pair(temp, filename);
        }

};

class Object {
    public:
        std::pair<float, float> pos; 
        std::list<Symbol> cilinder;

        Object (float x, float y) {
            pos = std::make_pair(x, y);

            for (auto i: n_symbols) {
                cilinder.emplace_back(Symbol(""));
            }

        }

        Object(std::pair<float, float> elem) {
            pos = elem;
        }

        /*bool operator() (const std::pair<sf::CircleShape, Object> pair) {
            return (pair.second.pos.first == pos.first && pair.second.pos.second == pos.second);
        }*/

    private:
        int n_symbols = 12;
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
        int nballs = 50;
};

class Game {
    public:
        int crdts;
        int state;
        int games;
        Balls gm_object = Balls();

        Game() {
            crdts = 10000;
            games = 0;
            state = GM_START;
        }

        virtual ~Game() {};

        void game_handler(const std::pair<float, float>* key_press) {
            gm_object.update_pos();

            std::pair<sf::CircleShape, Object>* element = find_closest(key_press);

            if(element)
                gm_object.del_element(element);

            return;
        }

       std::pair<sf::CircleShape, Object>* find_closest(const std::pair<float, float>* key_press) {
            int i = 0;

            for (auto &b: gm_object.balls) {
                if(b.first.getGlobalBounds().contains(key_press->first, key_press->second)) {
                    return &b;
                }
            }

            std::cout << "not found" << std::endl;
            return nullptr;
        }

        void add_credits() {
            crdts++;
        }

        int main_menu(int in) {
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
                    return -1;
            }            
            return 0;
        }
};
