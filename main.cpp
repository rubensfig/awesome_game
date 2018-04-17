#include<iostream>
#include <list>
#include <algorithm>
#include <assert.h>

#include "classes.cpp"

//void options_tuple(std::tuple<string, int>* options) {
//}
int main() {

    Game::Game loop = Game::Game();

    ::std::string choice = "";
    loop.menu_options();

    while (loop.state != GM_EXIT) {
        ::std::cout << ::std::endl;
        ::std::cout << "Enter choice $ ";
        ::std::cin >> choice;

        loop.call_function(&choice);
    }
}

