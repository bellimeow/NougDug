//
// Created by isade842 on 12/5/17.
//

#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "PlayState.h"


void Game::run()
{
    unsigned int display_size_multiplier{3};

    sf::Window window(sf::VideoMode(256*display_size_multiplier, 288*display_size_multiplier), "Noug Dug");


    change_state(states[0], current_state);

    while(window.isOpen())
    {
        update();

        sf::Event action;

        while(window.pollEvent(action))
        {
            if (action.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

Game::Game()
{
    //MenuState* menu_state{new MenuState};
    PlayState* play_state{new PlayState(this)};
    //EndState* end_state{new EndState};

    //push_state(menu_state);
    push_state(play_state);
    //push_state(end_state);

    std::cout << "Game is being created!" << std::endl;
}

void Game::change_state(AbstractGameState* state, int state_index)
{
    state->initialize();
    current_state = state_index;
}

void Game::push_state(AbstractGameState* state)
{
    states.push_back(state);
}

void Game::update()
{
    states[current_state]->update();
}

void get_state()
{

}
