#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

class Dirt : public Block
{

    private:


    public:

        Dirt(int depth);
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite dirt_sprite) override ;
        void animate() override ;
        sf::Texture get_sprite_sheet() override ;

};

#endif