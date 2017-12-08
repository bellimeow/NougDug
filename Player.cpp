//
// Created by isade842 on 12/8/17.
//

#include "Player.h"

const int Player::get_lives() const
{
    return lives;
}

const int Player::get_step() const
{
    return step;
}

void Player::set_position(int row, int column)
{
    Player::current_y = row;
    Player::current_x = column;
}

int Player::get_current_x() const {
    return current_x;
}

int Player::get_current_y() const {
    return current_y;
}
