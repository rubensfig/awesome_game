#define GM_START 0
#define GM_PAUSED 1
#define GM_PLAY 2
#define GM_EXIT 3

#define MIN_BET 1
#define MAX_BET 100

#define N_CILINDERS 3

class Object {
    public:
        std::pair<float, float> pos;

        Object (float x, float y) {
            pos = std::make_pair(x, y);
        }

        Object(std::pair<float, float> elem) {
            pos = elem;
        }
};

class Symbol {
    public:
        std::string piece;
        sf::Sprite img;
        std::tuple<float, float, float, float> graph_coor;
        int mult;

        Symbol(std::string type, int multiplier, float x1,  float y1, float x2, float y2) {
            piece = type;
            mult = multiplier;

            graph_coor = std::make_tuple(x1, y1, x2, y2);

            img.setColor(sf::Color::White);
        }
};

class Cilinder {
    public:
        std::pair<float, float> loc;
        std::vector<Symbol> cilinder;
        int pos;

        Cilinder (float x, float y) {
            pos = 0;
            loc = std::make_pair(x, y);

            cilinder.emplace_back(Symbol("A", 3, 136, 228, 224, 224));
            cilinder.emplace_back(Symbol("A", 3, 150, 230, 224, 224));

            cilinder.emplace_back(Symbol("B", 2, 120, 536, 257, 256));
            cilinder.emplace_back(Symbol("B", 2, 120, 536, 257, 256));
            cilinder.emplace_back(Symbol("C", 2, 452, 188, 208, 293));
            cilinder.emplace_back(Symbol("C", 2, 452, 188, 208, 293));

            cilinder.emplace_back(Symbol("D", 1, 410, 610, 293, 155));
            cilinder.emplace_back(Symbol("D", 1, 410, 610, 293, 155));
            cilinder.emplace_back(Symbol("E", 1, 734, 211, 257, 257));
            cilinder.emplace_back(Symbol("E", 1, 734, 211, 257, 257));
            cilinder.emplace_back(Symbol("F", 1, 734, 532, 257, 257));
            cilinder.emplace_back(Symbol("F", 1, 734, 532, 257, 257));
        }

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

class Game {
    public:
        int crdts;
        int state;
        int games;
        int bet = 10;
        int gain = 0;
        std::vector<Cilinder> slots;

        Game() {
            crdts = 10000;
            games = 0;
            state = GM_START;

            slots.emplace_back(200.0, 400.0);
            slots.emplace_back(500.0, 400.0);
            slots.emplace_back(800.0, 400.0);
        }

        virtual ~Game() {};

        void game_handler() {
            std::cout << "GAME " << std::endl;
            int pos;

            for (int i = 0; i < N_CILINDERS; i++) {
                pos = std::rand() % 11;
                std::cout << slots.at(i).cilinder.at(pos).piece << std::endl;
                slots.at(i).pos = pos;
            }

            gain = award_calc(slots.at(0).cilinder.at(slots.at(0).pos).mult,
                              slots.at(1).cilinder.at(slots.at(1).pos).mult,
                              slots.at(2).cilinder.at(slots.at(2).pos).mult);

            crdts += gain;
            state = GM_START;
            return;
        }

        int award_calc(int a, int b, int c) {
            if (a != b || a != c)
                return 0;

            return a*bet;
        }

        void add_credits() {
            crdts++;
        }

        int main_menu(int in) {
            int opt = 0;
            
            //0 = choose bet
            //1 = play game
            //2 = pause game
            //3 = exit

            //std::cout << in << std::endl;
            switch(in) {
                case 0:
                    if (crdts <= 0)
                        break;
                    crdts -= bet;
                    state = GM_PLAY;
                    break;
                case 1:
                    state = GM_EXIT;
                    break;
                default:
                    return -1;
            }            
            return 0;
        }
};
