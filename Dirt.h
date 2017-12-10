#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

class Dirt : Block
{

private:


public:

    Dirt(int depth);
        void draw(sf::RenderWindow*);
    void animate() override;

};

#endif