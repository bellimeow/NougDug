#ifndef TUNNEL_H
#define TUNNEL_H

#include "Block.h"

class Tunnel : public Block
{

    private:
        sf::Texture four_way;
        SpriteType

    public:
        Tunnel(int depth);

        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite dirt_sprite) override ;

        void animate() override;

        sf::Texture get_sprite_sheet() override ;
        bool check_passable(std::string character);

        const std::string &get_i_am_a() const override;
        void set_position(int y, int x) override;

};

#endif