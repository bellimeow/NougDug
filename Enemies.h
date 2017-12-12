#ifndef ENEMIES_H
#define ENEMIES_H

#include "Character.h"

class Enemies : public Character
{
    protected:
        double hunt_timer;
        bool can_hunt;
        bool is_eating;

        void patrol_path();
        void ghost_hunt();
        void start_hunt();

    public:
        Enemies(int lives);
        bool in_hunt_range();
};


#endif