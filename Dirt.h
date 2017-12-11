#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

class Dirt : public Block
{

    private:
        sf::Texture texture;
        sf::Texture Sprite::get_sprite_sheet();

    public:
        //std::string me{"Dirt"};

        Dirt(int depth);
        void draw(sf::RenderWindow* window, int row, int column, sf::Texture const &my_texture) ;
        void animate() override;

};

#endif