//
// Created by isade842 on 12/8/17.
//

#include <iostream>
#include "Player.h"

Player::Player()
        : Character(3, 1)
{
    texture = get_sprite_sheet();
}

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



sf::Texture Player::get_sprite_sheet()
{
    sf::Texture player_sheet {*Sprite::sprite_sheets["player"]};

    return player_sheet;
}

void Player::draw( sf::RenderWindow *window, int row, int column, sf::Sprite player_sprite )
{
    std::map<int, SpriteType> player_map{
            {1, SpriteType::FRONT}, {2, SpriteType::FRONT_R_FOOT}, {3, SpriteType::FRONT_L_FOOT}, {4, SpriteType::WIN},
            {5, SpriteType::RIGHT}, {6, SpriteType::RIGHT_R_FOOT}, {7, SpriteType::RIGHT_L_FOOT},
            {8, SpriteType::LEFT},  {9, SpriteType::LEFT_R_FOOT},  {10, SpriteType::LEFT_L_FOOT},
            {11, SpriteType::BACK}, {12, SpriteType::BACK_R_FOOT}, {13, SpriteType::BACK_L_FOOT}, {14, SpriteType::DEATH} };

    player_sprite.setTexture(texture);
    player_sprite.setTextureRect(Sprite::extract_texture_position(player_map[1]));

    Sprite::draw( window, row, column, player_sprite);
}

void Player::animate()
{
    std::cout << "Woo\n";
}

void Player::move()
{

}
