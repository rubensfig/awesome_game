#include <map>
#include <vector>

namespace Game {

    // Defined game states for this game
    #define GM_BET 0
    #define GM_PLAY 1
    #define GM_EXIT 2
    
    // Define the allowed betting interval
    #define MIN_BET 1
    #define MAX_BET 10
    
    // Define the allowed number of cilinders in the game
    #define N_CILINDERS 3

    /*
     * Basic class to handle each piece inserted in the slot cilinder 
     * */
    class Symbol {
        public:
            ::std::string piece;
            int mult;

            Symbol(::std::string type, int multiplier) {
                piece = type;
                mult = multiplier;
            }
    };

    /*
     * Handles all the pieces on each slot
     */
    class Cilinder {
        public:
            ::std::vector<Symbol> cilinder;
            int pos = 0;

            Cilinder () {
                cilinder.emplace_back(Symbol("A", 15));
                cilinder.emplace_back(Symbol("A", 15));

                cilinder.emplace_back(Symbol("B", 5));
                cilinder.emplace_back(Symbol("B", 5));
                cilinder.emplace_back(Symbol("C", 5));
                cilinder.emplace_back(Symbol("C", 5));

                cilinder.emplace_back(Symbol("D", 1));
                cilinder.emplace_back(Symbol("D", 1));
                cilinder.emplace_back(Symbol("E", 1));
                cilinder.emplace_back(Symbol("E", 1));
                cilinder.emplace_back(Symbol("F", 1));
                cilinder.emplace_back(Symbol("F", 1));
            }
    };

    /* 
     * Main game handler, provides the main menu, the representation of the game state, 
     * number of credits, and the main game logic 
     * */
    class Game {
        public:

            typedef void (Game::*f_ptr)(void); 
            std::map<::std::string, f_ptr> f_map;

            int crdts;
            int state;
            int games;
            int bet = -1;
            int gain = 0;
            ::std::vector<Cilinder> slots;

            Game() {
                crdts = 10000;
                games = 0;
                state = GM_BET;
                for (int i = 0; i < 3; i++)
                    slots.emplace_back(Cilinder());

                f_map["add"] = &Game::add_credits;
                f_map["bet"] = &Game::make_bet;
                f_map["options"] = &Game::menu_options;
                f_map["play"]= &Game::game_handler;
                f_map["exit"] = &Game::exit;
            }

            virtual ~Game() {};

            void game_handler(void) {
                int pos;

                crdts -= bet;

                if (bet < 0){
                    ::std::cout << "Bet cannot be -1" << ::std::endl;

                    ::std::string bet = "bet";
                    call_function(&bet);
                    return;
                }

                ::std::cout << "Game" << ::std::endl;
                ::std::cout << "Available credits " + ::std::to_string(crdts) << ::std::endl;
                ::std::cout << "Current bet " + ::std::to_string(bet) << ::std::endl;
                ::std::cout << "Result ";

                for (int i = 0; i < N_CILINDERS; i++) {
                    pos = std::rand() % 11;
                    ::std::cout << slots.at(i).cilinder.at(pos).piece << " "; 
                    slots.at(i).pos = pos;
                }

                ::std::cout << ::std::endl;

                gain = award_calc(&slots.at(0).cilinder.at(slots.at(0).pos),
                                  &slots.at(1).cilinder.at(slots.at(1).pos),
                                  &slots.at(2).cilinder.at(slots.at(2).pos));

                print_award(&gain);
                crdts += gain;

                ::std::string again = "y";
                ::std::cout << "Play Again? (y/n)"; 
                ::std::cin >> again;

                if (again == "n")
                    state == GM_BET;
                else {
                    ::std::string play = "play";
                    call_function(&play);
                }
                
                return;
            }

            /*
             * The awards are calculated with each symbol multiplier, for example:
             * Results: A A A
             * Multiplier for A: 3
             * Bet : 10
             * Award : Multiplier*Bet = 3*10 = 30 
             * */
            int award_calc(Symbol* p1, Symbol* p2, Symbol* p3) {
                if (p1->piece != p2->piece || p1->piece != p3->piece)
                    return 0;

                return p1->mult*bet;
            }

            void print_award(int* gain){
                if (*gain == 0) {
                    ::std::cout << "Award ";
                    ::std::cout << *gain << ::std::endl;
                } else {
                    ::std::cout << "Award ";
                    ::std::cout << *gain;
                    ::std::cout << "( ";
                    ::std::cout << bet;
                    ::std::cout << " x ";
                    ::std::cout << slots.at(0).cilinder.at(slots.at(0).pos).mult;
                    ::std::cout << " ) " << ::std::endl; 
                }
            }

            void add_credits(void) {
                bet = -1;
                int crdt_add = 0;
                while (crdt_add == 0) {
                    ::std::cout << "Add credits $ ";
                    ::std::cin >> crdt_add;
                }
                crdts += crdt_add;
            }

            void make_bet(void){
                bet = -1;
                while (bet < MIN_BET or bet > MAX_BET) {
                    ::std::cout << "Make Bet (" << ::std::to_string(MIN_BET) << " to " << ::std::to_string(MAX_BET) << ")$ ";
                    ::std::cin >> bet;
                }
                ::std::cout << "Current bet " << bet << ::std::endl;
            }
            
            /*
             * Handles the function calling logic, removes the need for a 
             * switch case instruction by passing the pointer to each function 
             * */
            void call_function(const ::std::string* choice) {
                auto it = ::std::find(options.begin(), options.end(), *choice);
                if(it == options.end())
                    return;
                    
                f_ptr fp = f_map[*choice];
                (this->*fp)();
            }

            void menu_options() {
                ::std::cout << "bet  : make a bet" << ::std::endl;
                ::std::cout << "play : play the game" << ::std::endl;
                ::std::cout << "options : see this menu" << ::std::endl;
                ::std::cout << "exit : exit game" << ::std::endl;
            }

            void exit(){
                state = GM_EXIT;
            }
        private:
            ::std::list<::std::string> options = {"add", "bet", "play", "options", "exit"};
    };
}
