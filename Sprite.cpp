//
// Created by seblu114 on 12/7/17.
//


#include <string>
#include "Sprite.h"
#include "Game.h"
#include <iostream>

const std::string Sprite::sprite_sheet_path = "./documents/Nougdug";


void Sprite::draw(sf::RenderWindow* window_ptr, int row, int column)
{

    //sf::Sprite sprite;
    sf::RectangleShape sprite{sf::Vector2f{16 * Game::DISPLAY_SIZE_MULTIPLIER, 16 * Game::DISPLAY_SIZE_MULTIPLIER}};
    //sprite.setFillColor(sf::Color::Blue);
    sprite.setTexture(&texture);
    //sprite.setScale(sf::Vector2f{16 * Game::DISPLAY_SIZE_MULTIPLIER, 16 * Game::DISPLAY_SIZE_MULTIPLIER});
    sprite.setPosition(sf::Vector2f((16*column*Game::DISPLAY_SIZE_MULTIPLIER), (16*row*Game::DISPLAY_SIZE_MULTIPLIER)));
    window_ptr->draw(sprite);
}


void Sprite::animate()
{

}


void Sprite::load_sprite_sheets()
{
    std::array<std::string, 10> file_names
            {
                    "player", "demodog", "demogorgon",
                    "dirt", "tunnel", "rock",
                    "nougat", "roots", "extra_points",
                    "projectile"
            };

    sf::Texture _sprite_sheet;

    for (int i = 0; i < file_names.size(); ++i)
    {
        sprite_sheets[file_names[i]] = new sf::Texture;

        if (!sprite_sheets[file_names[i]]->loadFromFile( sprite_sheet_path + file_names[i] + ".png" ))
        {
            std::cerr << "Couldn't open " + file_names[i] + " sprite sheet file!";
        }
    }
}

Sprite::Sprite()
{

}

void Sprite::set_position( int row, int column )
{

}

sf::IntRect extract_texture_position(SpriteType sprite_type)
{
/*      ROW 1 : | 0 | 1 | 2 | 3 |
 *      ROW 2 : | 4 | 5 | 6 | 7 |
 *      ROW 3 : | 8 | 9 |10 |11 |
 *      ROW 4 : |12 |13 |14 |15 |
 *
 * Hur sprites är ordnade i en fil.     */

    std::vector<sf::IntRect> sheet_coordinates
            {
                {0,  0, 16, 16}, {17,  0, 16, 16}, {33,  0, 16, 16}, {49,  0, 16, 16},
                {0, 17, 16, 16}, {17, 17, 16, 16}, {33, 17, 16, 16}, {49, 17, 16, 16},
                {0, 33, 16, 16}, {17, 33, 16, 16}, {33, 33, 16, 16}, {49, 33, 16, 16},
                {0, 49, 16, 16}, {17, 49, 16, 16}, {33, 49, 16, 16}, {49, 49, 16, 16}
            };

    switch (sprite_type)
    {
             /*****       ROW 1        *****/
            /*** sprite position 0 ***/
        case SpriteType::FRONT :
        case SpriteType::DIRT_DEPTH_1 :
        case SpriteType::TUNNEL_D1_4 :
        case SpriteType::ROCK :
        case SpriteType::NOUGAT :
        case SpriteType::ROOTS_1 :
        case SpriteType::EXTRA_POINT :
        case SpriteType::PROJECTILE :
            return sheet_coordinates[0];

            /*** sprite position 1 ***/
        case SpriteType::FRONT_R_FOOT :
        case SpriteType::DIRT_DEPTH_2 :
        case SpriteType::TUNNEL_D1_CORNER :
        case SpriteType::ROOTS_2 :
            return sheet_coordinates[1];

            /*** sprite position 2 ***/
        case SpriteType::FRONT_L_FOOT :
        case SpriteType::DIRT_DEPTH_3 :
        case SpriteType::TUNNEL_D1_2 :
        case SpriteType::ROOTS_3 :
            return sheet_coordinates[2];

            /*** sprite position 3 ***/
        case SpriteType::WIN:
        case SpriteType::DIRT_DEPTH_4 :
        case SpriteType::TUNNEL_D1_1 :
        case SpriteType::ROOTS_4 :
            return sheet_coordinates[3];

            /*****       ROW 2        *****/
            /*** sprite position 4 ***/
        case SpriteType::RIGHT:
            return sheet_coordinates[4];

            /*** sprite position 5 ***/
        case SpriteType::RIGHT_R_FOOT:
        case SpriteType::TUNNEL_D2_CORNER:
            return sheet_coordinates[5];

            /*** sprite position 6 ***/
        case SpriteType::RIGHT_L_FOOT :
        case SpriteType::TUNNEL_D2_2 :
            return sheet_coordinates[6];

            /*** sprite position 7 ***/
        case SpriteType::TUNNEL_D2_1 :
            return sheet_coordinates[7];

            /*****       ROW 3        *****/
            /*** sprite position 8 ***/
        case SpriteType::LEFT :
            return sheet_coordinates[8];

            /*** sprite position 9 ***/
        case SpriteType::LEFT_R_FOOT :
        case SpriteType::TUNNEL_D3_CORNER :
            return sheet_coordinates[9];

            /*** sprite position 10 ***/
        case SpriteType::LEFT_L_FOOT :
        case SpriteType::TUNNEL_D3_2 :
            return sheet_coordinates[10];

            /*** sprite position 11 ***/
        case SpriteType::TUNNEL_D3_1 :
            return sheet_coordinates[11];

            /*****       ROW 4        *****/
            /*** sprite position 12 ***/
        case SpriteType::BACK :
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