//
// Created by seblu114 on 12/7/17.
//


#include <string>
#include "Sprite.h"
#include "Game.h"
#include <iostream>

const std::string Sprite::sprite_sheet_path = "textures/";

std::map< std::string, sf::Texture*> Sprite::sprite_sheets{};

Sprite::Sprite()
{}

Sprite::Sprite(std::string object)
        : i_am_a{object}
{}

void Sprite::draw(sf::RenderWindow* window_ptr, int row, int column, sf::Sprite& sprite)
{
    sprite.setScale(sf::Vector2f{Game::DISPLAY_SIZE_MULTIPLIER, Game::DISPLAY_SIZE_MULTIPLIER});
    sprite.move(sf::Vector2f((16*column*Game::DISPLAY_SIZE_MULTIPLIER), (16*row*Game::DISPLAY_SIZE_MULTIPLIER)));

    window_ptr->draw(sprite);
}


void Sprite::animate()
{

}


void Sprite::load_sprite_sheets()
{
    std::array<std::string, 13> file_names
            {
                    "player", "demodog", "demogorgon",
                    "dirt", "tunnel", "tunnel4", "rock",
                    "nougat", "roots", "extra_points",
                    "projectile", "board_background",
                    "ghost"
            };

    for (int i = 0; i < file_names.size(); ++i)
    {
        Sprite::sprite_sheets[file_names[i]] = new sf::Texture;

        if (!Sprite::sprite_sheets[file_names[i]]->loadFromFile( sprite_sheet_path + file_names[i] + ".png" ))
        {
            std::cerr << "Couldn't open " + file_names[i] + " sprite sheet file!" << std::endl;
        }
    }
}

sf::Texture Sprite::get_sprite_sheet()
{
    return sf::Texture();
}

sf::Texture* Sprite::get_sprite_sheet(std::string object_type)
{
    sf::Texture* sheet{sprite_sheets[object_type]};

    return sheet;
}

sf::IntRect Sprite::extract_texture_position(SpriteType sprite_type)
{
/*      ROW 1 : | 0 | 1 | 2 | 3 |
 *      ROW 2 : | 4 | 5 | 6 | 7 |
 *      ROW 3 : | 8 | 9 |10 |11 |
 *      ROW 4 : |12 |13 |14 |15 |
 *
 * Hur sprites är ordnade i en fil.     */

    std::vector<sf::IntRect> sheet_coordinates
            {
                {0,  0, 16, 16}, {17,  0, 16, 16}, {34,  0, 16, 16}, {51,  0, 16, 16},
                {0, 17, 16, 16}, {17, 17, 16, 16}, {34, 17, 16, 16}, {51, 17, 16, 16},
                {0, 34, 16, 16}, {17, 34, 16, 16}, {34, 34, 16, 16}, {51, 34, 16, 16},
                {0, 51, 16, 16}, {17, 51, 16, 16}, {34, 51, 16, 16}, {51, 51, 16, 16}
            };

    switch (sprite_type)
    {
             /*****       ROW 1        *****/
            /*** sprite position 0 ***/
        case SpriteType::FRONT :
        case SpriteType::DIRT_DEPTH_1 :
        case SpriteType::TUNNEL_4 :
        case SpriteType::TUNNEL_D1_3 :
        case SpriteType::ROCK :
        case SpriteType::NOUGAT :
        case SpriteType::ROOTS_1 :
        case SpriteType::EXTRA_POINT :
        case SpriteType::PROJECTILE :
        case SpriteType::ZERO :
        case SpriteType::HEART :
        case SpriteType::GHOST_FRONT :
            return sheet_coordinates[0];

            /*** sprite position 1 ***/
        case SpriteType::FRONT_R_FOOT :
        case SpriteType::DIRT_DEPTH_2 :
        case SpriteType::TUNNEL_D1_CORNER :
        case SpriteType::ROOTS_2 :
        case SpriteType::ONE :
        case SpriteType::EMPTY_HEART :
        case SpriteType::GHOST_FRONT_2 :
            return sheet_coordinates[1];

            /*** sprite position 2 ***/
        case SpriteType::FRONT_L_FOOT :
        case SpriteType::DIRT_DEPTH_3 :
        case SpriteType::TUNNEL_D1_2 :
        case SpriteType::ROOTS_3 :
        case SpriteType::TWO :
            return sheet_coordinates[2];

            /*** sprite position 3 ***/
        case SpriteType::WIN:
        case SpriteType::DIRT_DEPTH_4 :
        case SpriteType::TUNNEL_D1_1 :
        case SpriteType::ROOTS_4 :
        case SpriteType::THREE :
            return sheet_coordinates[3];

            /*****       ROW 2        *****/
            /*** sprite position 4 ***/
        case SpriteType::RIGHT:
        case SpriteType::TUNNEL_D2_3 :
        case SpriteType::FOUR :
            return sheet_coordinates[4];

            /*** sprite position 5 ***/
        case SpriteType::RIGHT_R_FOOT:
        case SpriteType::TUNNEL_D2_CORNER:
        case SpriteType::FIVE :
            return sheet_coordinates[5];

            /*** sprite position 6 ***/
        case SpriteType::RIGHT_L_FOOT :
        case SpriteType::TUNNEL_D2_2 :
        case SpriteType::SIX :
            return sheet_coordinates[6];

            /*** sprite position 7 ***/
        case SpriteType::TUNNEL_D2_1 :
        case SpriteType::RIGHT_R_FOOT_2 :
        case SpriteType::SEVEN :
            return sheet_coordinates[7];

            /*****       ROW 3        *****/
            /*** sprite position 8 ***/
        case SpriteType::LEFT :
        case SpriteType::TUNNEL_D3_3 :
        case SpriteType::EIGHT :
            return sheet_coordinates[8];

            /*** sprite position 9 ***/
        case SpriteType::LEFT_R_FOOT :
        case SpriteType::TUNNEL_D3_CORNER :
        case SpriteType::NINE :
            return sheet_coordinates[9];

            /*** sprite position 10 ***/
        case SpriteType::LEFT_L_FOOT :
        case SpriteType::TUNNEL_D3_2 :
            return sheet_coordinates[10];

            /*** sprite position 11 ***/
        case SpriteType::TUNNEL_D3_1 :
        case SpriteType::LEFT_R_FOOT_2 :
            return sheet_coordinates[11];

            /*****       ROW 4        *****/
            /*** sprite position 12 ***/
        case SpriteType::BACK :
        case SpriteType::TUNNEL_D4_3 :
            return sheet_coordinates[12];

            /*** sprite position 13 ***/
        case SpriteType::BACK_R_FOOT :
        case SpriteType::TUNNEL_D4_CORNER :
            return sheet_coordinates[13];

            /*** sprite position 14 ***/
        case SpriteType::BACK_L_FOOT :
        case SpriteType::TUNNEL_D4_2 :
            return sheet_coordinates[14];

            /*** sprite position 15 ***/
        case SpriteType::DEATH :
        case SpriteType::TUNNEL_D4_1 :
            return sheet_coordinates[15];

        default:
            break;
    }
}

void Sprite::set_position( int y, int x )
{
    current_position.y = y;
    current_position.x = x;

}

void Sprite::set_real_position( int y, int x )
{
    real_position.y = y;
    real_position.x = x;
}

const std::string &Sprite::get_i_am_a() const
{
    return i_am_a;
}

int Sprite::get_current_x() const
{
    return current_position.x;
}

int Sprite::get_current_y() const
{
    return current_position.y;
}

sf::Vector2i Sprite::get_current_pos() const
{
    return current_position;
}

sf::Vector2i Sprite::get_real_pos() const
{
    return real_position;
}

void Sprite::set_real_position()
{
    set_real_position( current_position.y * 16 * scale, current_position.x * 16 * scale );
}

bool Sprite::get_mark_for_delete() const
{
    return mark_for_delete;
}

void Sprite::set_mark_for_delete( bool mark_for_delete )
{
    Sprite::mark_for_delete = mark_for_delete;
}

void Sprite::move()
{

}
