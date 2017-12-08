#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "AbstractGameState.h"
#include "PlayState.h"

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

    public:
        int current_state{};
        bool win{false};

        Game();
        void change_state(AbstractGameState* state, int state_index);
        void push_state(AbstractGameState* state);
        void run();
        void update();
};
#endif