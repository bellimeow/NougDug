#include <iostream>
#include "EndState.h"
#include "Sprite.h"

EndState::EndState( Game* game, sf::RenderWindow* window_ptr )
        : game{ game }, window_ptr{ window_ptr }
{

}

void EndState::player_input()
{
    change_state();
}

void EndState::change_state()
{
    high_score = 0;
    game->change_state(1);
}

void EndState::initialize()
{
}

void EndState::update()
{
    draw();
}

void EndState::draw()
{
    std::string high_score = std::to_string(get_high_score());

    sf::Font font;
    if (!font.loadFromFile("textures/lilliput steps.ttf"))
    {
        std::cerr << "Couldn't load font!" << std::endl;
    }
    sf::Text game_over;
    game_over.setFont( font );

    if ( game->win )
    {
        game_over.setString( "YOU WIN" );
        game_over.setColor( sf::Color::Blue );
    }
    else
    {
        game_over.setString( "GAME OVER" );
        game_over.setColor( sf::Color::Red );
    }

    game_over.setCharacterSize( 70 );
    sf::FloatRect game_over_rect = game_over.getLocalBounds();
    game_over.setOrigin( game_over_rect.left + game_over_rect.width/2.0f,
                    game_over_rect.top  + game_over_rect.height/2.0f );
    game_over.setPosition(sf::Vector2f((game->get_window_width()*Game::DISPLAY_SIZE_MULTIPLIER)/2.0f,(game->get_window_height()*Game::DISPLAY_SIZE_MULTIPLIER)/4.0f));

    window_ptr->draw(game_over);

    create_high_score();
}

void EndState::check_state()
{

}

void EndState::create_high_score()
{
    sf::Font font;
    if (!font.loadFromFile("textures/lilliput steps.ttf"))
    {
        std::cerr << "Couldn't load font!" << std::endl;
    }
    sf::Text game_over;
    game_over.setFont( font );

    sf::Text text;
    text.setFont( font );
    text.setString( " Your high score \n\n       " +  high_score);
    text.setCharacterSize( 40 );
    text.setColor( sf::Color::White );
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin( textRect.left + textRect.width/2.0f,
                    textRect.top  + textRect.height/2.0f );
    text.setPosition(sf::Vector2f((game->get_window_width()*Game::DISPLAY_SIZE_MULTIPLIER)/2.0f,(game->get_window_height()*Game::DISPLAY_SIZE_MULTIPLIER)/2.0f));

    window_ptr->draw(text);
}

