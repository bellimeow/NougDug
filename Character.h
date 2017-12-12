#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <fstream>
#include "Sprite.h"

class Character : public Sprite
{
protected:
    struct position;

    const int lives{};
    const int step{};


    struct position
    {
        double x{};
        double y{};
    };

public:
        Character( int lives, int step, std::string object );

       // virtual void move() = 0;
};




#endif