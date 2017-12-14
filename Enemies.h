#ifndef ENEMIES_H
#define ENEMIES_H

#include "Character.h"

class Enemies : public Character
{
    protected:
        double hunt_timer;
        bool can_hunt;
        bool is_eating;

        virtual void patrol(std::array<std::array<Sprite*, 3>, 3> possible_pos, sf::Clock &time);
        virtual void ghost_hunt();
        virtual void start_hunt();

    public:
        Enemies(int lives, std::string object);
        bool in_hunt_range();
};


#endif