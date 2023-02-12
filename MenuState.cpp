#include <iostream>
#include "MenuState.h"

MenuState::MenuState( Game* game, sf::RenderWindow* window_ptr )
        : game{game}, window_ptr{window_ptr}
{

}

void MenuState::player_input()
{
    change_state();
}

void MenuState::change_state()
{
    game->change_state(1);
}

void MenuState::update()
{
    draw();
}

void MenuState::draw()
{
    sf::Texture background_texture;

    if (!background_texture.loadFromFile("textures/title_background.png"))
    {
        std::cerr << "Could not load background!\n";
    }
    sf::RectangleShape background{ sf::Vector2f( game->get_window_width() * Game::DISPLAY_SIZE_MULTIPLIER, game->get_window_height() * Game::DISPLAY_SIZE_MULTIPLIER ) };

    background.setTexture(&background_texture);;
    background.setPosition(0,0);


    sf::Texture title_texture;

    if (!title_texture.loadFromFile("textures/title.png"))
    {
        std::cerr << "Could not load title!\n";
    }

    sf::RectangleShape title{sf::Vector2f(game->get_window_width() * Game::DISPLAY_SIZE_MULTIPLIER, ( int )( ( game->get_window_height() * Game::DISPLAY_SIZE_MULTIPLIER ) / 2.5 ) ) };
    title.setTexture( &title_texture );

    title.setOrigin( game->get_window_width()/0.7f, game->get_window_height()/0.7f );
    title.setPosition(sf::Vector2f((game->get_window_width()*Game::DISPLAY_SIZE_MULTIPLIER)/2.0f,(game->get_window_height()*Game::DISPLAY_SIZE_MULTIPLIER)/2.0f));

    sf::Texture start_texture;
    sf::RectangleShape start{sf::Vector2f(200, 150)};
    if (!start_texture.loadFromFile("textures/Start.png"))
    {
        std::cerr << "Could not load start!";
    }

    start.setTexture( &start_texture );
    start.setPosition(sf::Vector2f(284, 440));

    window_ptr->draw(background);
    window_ptr->draw(title);
    window_ptr->draw(start);
}

void MenuState::initialize()
{

}

void MenuState::check_state()
{

}

void MenuState::create_high_score()
{

}


