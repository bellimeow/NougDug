#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

class Dirt : public Block
{

    private:
        sf::Texture texture;

    public:
        std::string me{"Dirt"};

        Dirt(int depth);
        void draw(sf::RenderWindow* window, int row, int column);
        void animate() override;
        sf::Texture get_sprite_sheet();

};

#endif