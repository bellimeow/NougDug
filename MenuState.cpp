//
// Created by seblu114 on 12/8/17.
//

#include <iostream>
#include "MenuState.h"

void MenuState::player_input()
{
    change_state();
}

void MenuState::change_state()
{
    game->change_state(1);
}

void MenuState::initialize()
{

}

void MenuState::update()
{
    draw();
}

void MenuState::draw()
{
    sf::Texture texture;
    if (!texture.loadFromFile("/home/isade842/Documents/TDP005/NougDug/documents/Nougdug/noug.png"))
    {
        std::cerr << "Rawr!\n";
    }
    sf::Texture* tp = &texture;
    sf::RectangleShape title{sf::Vector2f(768, 360)};
    title.setTexture(tp);

    sf::Texture start_texture;
    sf::RectangleShape start{sf::Vector2f(200, 150)};
    if (!start_texture.loadFromFile("/home/isade842/Documents/TDP005/NougDug/documents/Nougdug/Start.png"))
    {
        std::cerr << "Nope!";
    }
    sf::Texture* start_tp = &start_texture;
   start.setTexture( start_tp );

    start.setPosition(sf::Vector2f(284, 440));


// inside the main loop, between window.clear() and window.display()

    window_ptr->draw(title);
    window_ptr->draw(start);
}

MenuState::MenuState( Game* game, sf::RenderWindow* window_ptr )
        : game{game}, window_ptr{window_ptr}
{

}

void MenuState::play_again()
{

}

void MenuState::check_state()
{

}

int MenuState::get_high_score()
{
    return 0;
}

