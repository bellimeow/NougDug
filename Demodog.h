#ifndef DEMODOG_H
#define DEMODOG_H

#include "Enemies.h"

class Demodog : public Enemies
{
    private:


    public:
        Demodog();
        void animate() override;
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite &enemy_sprite) override;
        //void move(std::string direction);


        sf::Texture get_sprite_sheet() override ;



        bool check_not_passable( std::string ) override;

        void dinner_time();
};


#endif