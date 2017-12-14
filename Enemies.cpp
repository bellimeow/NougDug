//
// Created by seblu114 on 12/12/17.
//

#include "Enemies.h"

Enemies::Enemies(int lives, std::string object)
    : Character(lives, 1, object)
{

}

void Enemies::patrol(std::array<std::array<Sprite*, 3>, 3> possible_pos, sf::Clock &time)
{
    while(/*It'sAlive! or Time*/)
    {
        /* Murder and mayhem */
    };
}
