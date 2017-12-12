#ifndef DEMODOG_H
#define DEMODOG_H

#include "Enemies.h"

class Demodog : public Enemies
{
    private:


    public:
        Demodog();
        void animate() override;
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite enemy_sprite) override;
        void move(std::string direction);

        sf::Texture get_sprite_sheet() override ;

        const std::string &get_i_am_a() const override;
        void set_position(int y, int x) override;

        bool check_passable( std::string ) override;
};


#endif