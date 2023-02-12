//
// Created by isade842 on 12/8/17.
//

#include "Character.h"


Character::Character( int lives, int step, std::string object, int tick_len )
    : lives(lives), step(step), Sprite( std::move( object )), tick_len{tick_len}
{}

void Character::set_direction( const std::string &direction )
{
    Character::direction = direction;
}

const std::string &Character::get_direction() const
{
    return direction;
}

const int Character::get_lives() const
{
    return lives;
}

bool Character::is_is_alive() const
{
    return is_alive;
}

void Character::set_is_alive( bool is_alive )
{
    Character::is_alive = is_alive;
}


