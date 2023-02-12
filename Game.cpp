//
// Created by isade842 on 12/5/17.
//

#include "Game.h"

#include <iostream>
#include "PlayState.h"
#include "MenuState.h"
#include "EndState.h"

Game::Game()
{
    sf::RenderWindow* window_ptr{ &window };

    MenuState* menu_state{ new MenuState( this, window_ptr ) };
    PlayState* play_state{ new PlayState( this, window_ptr ) };
    EndState* end_state{ new EndState( this, window_ptr ) };

    push_state( menu_state );
    push_state( play_state );
    push_state( end_state );

    AbstractGameState::load_state_sheets();
    AbstractGameState::extract_number_textures();

    std::cout << "Game is being created!" << std::endl;
}

Game::~Game()
{
    remove();
}

void Game::run()
{
    window.create( sf::VideoMode(
                    window_width * DISPLAY_SIZE_MULTIPLIER,
                    window_height * DISPLAY_SIZE_MULTIPLIER ), "Noug Dug" );

    change_state( current_state );

    while ( window.isOpen() )
    {
        sf::Event action;
        window.clear( sf::Color::Black );

        while ( window.pollEvent( action ) )
        {
            if ( action.type == sf::Event::Closed )
            {
                window.close();
            }
            if ( action.type == sf::Event::KeyPressed )
            {
                states[current_state]->player_input();
            }
        }

        // draw everything here...
        // window.draw(...);
        states[current_state]->draw();
        update();

        // end the current frame
        window.display();
    }
}

void Game::change_state( int state_index )
{
    current_state = state_index;
    states[current_state]->initialize();
}

void Game::push_state( AbstractGameState* state )
{
    states.push_back( state );
}

void Game::update()
{
    states[current_state]->update();
}

int Game::get_window_width() const
{
    return window_width;
}

int Game::get_window_height() const
{
    return window_height;
}

void Game::remove()
{
    std::for_each( std::begin( states ), std::end( states ),
                   [](AbstractGameState* state ){ delete( state ); } );
}

