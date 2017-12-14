#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Block.h"

class Background : public Block
{

    private:


    public:

        Background(int depth);
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite &dirt_sprite) override;
        void animate() override;
        sf::Texture get_sprite_sheet() override;
        bool check_not_passable( std::string character) override;



};

#endif