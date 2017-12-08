//
// Created by isade842 on 12/5/17.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "PlayState.h"


void Game::run()
{
    unsigned int display_size_multiplier{3};

    sf::RenderWindow window(sf::VideoMode(256*display_size_multiplier, 288*display_size_multiplier), "Noug Dug");


    change_state(states[0], current_state);

    while(window.isOpen())
    {
        sf::Event action;

        while(window.pollEvent(action))
        {
            if (action.type == sf::Event::Closed)
            {
                window.close();
            }
            if (action.type == sf::Event::KeyPressed)
            {
                states[0]->player_input();
            }
        }

        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        sf::Texture texture;
        if (!texture.loadFromFile("/home/seblu114/Downloads/noug.png"))
        {
            std::cerr << "Rawr!\n";
        }
        sf::Texture* tp = &texture;
        sf::RectangleShape title{sf::Vector2f(768, 360)};
        title.setTexture(tp);

        window.draw(title);
        update();


        // end the current frame
        window.display();
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
