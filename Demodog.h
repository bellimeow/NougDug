#ifndef DEMODOG_H
#define DEMODOG_H

#include "Enemies.h"

class Demodog : public Enemies
{
    private:
        int current_x;
        int current_y;


    public:
        Demodog();
        void animate() override;
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite enemy_sprite) override;
        void move(std::string direction);

        sf::Texture get_sprite_sheet() override ;
};


#endif