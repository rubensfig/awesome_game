#include<iostream>
#include <list>
#include <assert.h>

#include <SFML/Graphics.hpp>
#include "classes.cpp"

void draw_all(Balls* balls, Buttons* btns, Buttons* counters, Buttons* games, sf::RenderWindow* window) {
    return;
}

int main() {

    Game loop = Game();

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

                if(loop.main_menu(move_btns.input(&key_press)) == 0)
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
