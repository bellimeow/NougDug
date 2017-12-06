#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include "Game.h"

class Game;

class AbstractGameState
{

    protected:
        int high_score{};
        Game* game{nullptr};

    public:
        virtual void check_state() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void initialize() = 0;
        virtual void play_again() = 0;
        virtual int get_high_score() = 0;
};

#endif