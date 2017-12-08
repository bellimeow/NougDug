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
    if (!texture.loadFromFile("/home/seblu114/Downloads/noug.png"))
    {
        std::cerr << "Rawr!\n";
    }
    sf::Texture* tp = &texture;
    sf::RectangleShape title{sf::Vector2f(768, 360)};
    title.setTexture(tp);

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Nope!";
    }
    text.setFont(font); // font is a sf::Font

// set the string to display
    text.setString("Press Any Key to Continue");

// set the character size
    text.setCharacterSize(24); // in pixels, not points!

// set the color
    text.setColor(sf::Color::White);

// set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setPosition(sf::Vector2f(50, 360));


// inside the main loop, between window.clear() and window.display()

    window_ptr->draw(title);
    window_ptr->draw(text);
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

