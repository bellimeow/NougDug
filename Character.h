#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <fstream>
#include "AbstractGameState.h"
#include "Board.h"

class Character : Sprite
{
protected:
    struct position;

    int lives{};
    double speed{};

    struct position
    {
        double x{};
        double y{};
    };

public:
    virtual void move();
};

#endif