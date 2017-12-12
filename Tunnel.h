#ifndef TUNNEL_H
#define TUNNEL_H

#include "Block.h"

class Tunnel : public Block
{

    private:
        sf::Texture four_way;

    public:
        Tunnel(int depth);

        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite dirt_sprite) override ;

        void animate() override;

        sf::Texture get_sprite_sheet() override ;

};

#endif