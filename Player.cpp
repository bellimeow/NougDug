//
// Created by isade842 on 12/8/17.
//

#include <iostream>
#include <sys/stat.h>
#include "Player.h"

Player::Player()
        : Character(3, 1, "player", 100)
{
    texture = get_sprite_sheet();
    direction = "down";
}

const int Player::get_step() const
{
    return step;
}

sf::Texture Player::get_sprite_sheet()
{
    sf::Texture player_sheet {*Sprite::sprite_sheets["player"]};

    return player_sheet;
}

void Player::draw( sf::RenderWindow *window, int row, int column, sf::Sprite& player_sprite )
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

}

bool Player::check_not_passable( std::string object ) const
{
    return (object == "rock" || object == "projectile");
}

bool Player::moving_object_collide( Sprite* object )
{
    return (object->get_current_pos() == current_position);
}

bool Player::get_can_shoot() const {
    return can_shoot;
}

bool Player::get_invulnerable() const {
    return invulnerable;
}

void Player::set_invulnerable( bool invulnerable )
{
    Player::invulnerable = invulnerable;
}

