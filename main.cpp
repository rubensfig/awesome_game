#include<iostream>
#include <list>
#include <assert.h>

#include <SFML/Graphics.hpp>
#include "classes.cpp"


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
