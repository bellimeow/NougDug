//
// Created by seblu114 on 12/10/17.
//

#include "Dirt.h"

Dirt::Dirt( int depth )
        : Block( depth, "dirt")
{
    texture = get_sprite_sheet();

}

void Dirt::animate()
{
    Sprite::animate();
}

void Dirt::draw( sf::RenderWindow * window, int row, int column, sf::Sprite& dirt_sprite)
{
    std::map<int, SpriteType> dirt_depth_map{ {1, SpriteType::DIRT_DEPTH_1},
                                              {2, SpriteType::DIRT_DEPTH_2},
                                              {3, SpriteType::DIRT_DEPTH_3},
                                              {4, SpriteType::DIRT_DEPTH_4} };

    dirt_sprite.setTexture(texture);
    dirt_sprite.setTextureRect(Sprite::extract_texture_position(dirt_depth_map[depth]));

    Sprite::draw( window, row, column, dirt_sprite);
}

sf::Texture Dirt::get_sprite_sheet()
{

     sf::Texture dirt_sheet {*Sprite::sprite_sheets["dirt"]};

    return dirt_sheet;

}

bool Dirt::check_not_passable( std::string character ) const
{
    return (character == "player" || character == "demogorgon" ||
            character == "demodog" || character == "nougat" ||
            character == "rock");
}
