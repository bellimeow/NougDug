#ifndef ROOTS_H
#define ROOTS_H

#include "Block.h"

class Rock : public Block
{

    private:

        bool falling;

    public:

        Rock(int depth);
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite dirt_sprite) override ;
        void animate() override;
        sf::Texture get_sprite_sheet() override ;

        bool check_passable( std::string character);

        const std::string &get_i_am_a() const override;
        void set_position(int y, int x) override;
};

#endif