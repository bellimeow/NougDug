#ifndef ROCK_H
#define ROCK_H

#include "Block.h"

class Rock : public Block
{

    private:

        bool falling;

    public:

        Rock(int depth);
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite &dirt_sprite) override ;
        void animate() override;
        sf::Texture get_sprite_sheet() override ;

        bool check_not_passable( std::string character);


};

#endif