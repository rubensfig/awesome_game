#include<iostream>
#include <list>
#include <assert.h>

#include <SFML/Graphics.hpp>
#include "classes.cpp"

void draw_all(std::vector<Cilinder> slots, Buttons* btns, Buttons* cntrs,Buttons* bet, sf::RenderWindow* window) {

    window->clear();

    for (auto &it: btns->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first, pos.pos.second);
        txt->setPosition(pos.pos.first, pos.pos.second);

        window->draw(*rect);
        window->draw(*txt);
    }

    int pos;
    sf::Texture tex;

    for (auto &it: slots) {
        pos = it.pos;
        it.cilinder.at(pos).img.setPosition(it.loc.first, it.loc.second);

        float pos1 = std::get<0>(it.cilinder.at(pos).graph_coor);
        float pos2 = std::get<1>(it.cilinder.at(pos).graph_coor);
        float pos3 = std::get<2>(it.cilinder.at(pos).graph_coor);
        float pos4 = std::get<3>(it.cilinder.at(pos).graph_coor);

        tex.loadFromFile("fig/casino_pieces.png", sf::IntRect(pos1, pos2, pos3, pos4));
        //tex->setSmooth(true);
        it.cilinder.at(pos).img.setTexture(tex, true);
        window->draw(it.cilinder.at(pos).img);
    }

    for (auto &it: cntrs->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first,pos.pos.second  + 30*6);
        txt->setPosition(pos.pos.first, pos.pos.second  + 30*6);

        window->draw(*rect);
        window->draw(*txt);
    }

    for (auto &it: bet->btns) {

        sf::RectangleShape* rect = &(std::get<0>(it));
        sf::Text* txt = &(std::get<2>(it));
        Object pos = std::get<1>(it);

        rect->setPosition(pos.pos.first, pos.pos.second + 35*7 );
        txt->setPosition(pos.pos.first, pos.pos.second  + 35*7);

        window->draw(*rect);
        window->draw(*txt);
}
    window->display();

    return;
}

int main() {

    Game loop = Game();

    Buttons move_btns = Buttons(3, true, "Red", {"change bet", "play", "exit"});
    Buttons counters = Buttons(1, false, "Blue", {""});
    Buttons bet = Buttons(1, false, "Blue", {""});

    sf::RenderWindow window(sf::VideoMode(1024, 768), "fmq_game");
    sf::Event event;
    std::pair<float, float> key_press;
    bool pressed = false;
    

    draw_all(loop.slots, &move_btns, &counters, &bet, &window);
    while (loop.state != GM_EXIT) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left){
                    key_press = std::make_pair(event.mouseButton.x, event.mouseButton.y);
                    pressed = true;
                }
        }

        //std::cout << loop.state << std::endl;

        switch(loop.state) {
            case GM_START:
                if (!pressed)
                    continue;
                loop.main_menu(move_btns.input(&key_press));
                //loop.main_menu(0);
                break;

            case GM_PLAY:
                if(loop.main_menu(move_btns.input(&key_press)) == 1)
                    continue;
                //if (!pressed)
                    //continue;
                loop.game_handler(); 
                
                break;
        }

        std::get<2>(counters.btns.front()).setString(std::to_string(loop.crdts));
        std::get<2>(bet.btns.front()).setString(std::to_string(loop.bet));

        draw_all(loop.slots, &move_btns, &counters, &bet, &window);
        pressed = false;
    }
}
