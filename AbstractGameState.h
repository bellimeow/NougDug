#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include <string>
#include "Game.h"

class Game;

class AbstractGameState
{

    protected:
        int high_score{};
        Game* game{nullptr};
        static std::string directory;
        static std::string level;

    public:
        virtual void check_state() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void initialize() = 0;
        virtual void play_again() = 0;
        virtual int get_high_score() = 0;
        virtual void player_input() = 0;
};

#endif