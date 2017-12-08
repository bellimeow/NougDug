#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

/*
 * 1 : PlayState
 * 2 : MenuState
 * 3 : EndState
 *
 * */
class AbstractGameState;


class Game
{
    private:
        std::vector<AbstractGameState*> states;
        unsigned int display_size_multiplier{3};

    public:
        int current_state{};
        bool win{false};
        sf::RenderWindow window;

        Game();
        void change_state(int state_index);
        void push_state(AbstractGameState* state);
        void run();
        void update();
};
#endif