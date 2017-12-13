//
// Created by seblu114 on 12/13/17.
//

#include "Background.h"

Background::Background( int depth )
        : Block( depth, "background")
{
    texture = get_sprite_sheet();

}

void Background::animate()
{
    Sprite::animate();
}

void Background::draw( sf::RenderWindow * window, int row, int column, sf::Sprite dirt_sprite)
{
    std::map<int, SpriteType> dirt_depth_map{ {1, SpriteType::DIRT_DEPTH_1},
                                              {2, SpriteType::DIRT_DEPTH_2},
                                              {3, SpriteType::DIRT_DEPTH_3},
                                              {4, SpriteType::DIRT_DEPTH_4} };

    dirt_sprite.setTexture(texture);
    dirt_sprite.setTextureRect(Sprite::extract_texture_position(dirt_depth_map[depth]));

    //Sprite::draw( window, row, column, dirt_sprite);
}

sf::Texture Background::get_sprite_sheet()
{

    sf::Texture dirt_sheet {*Sprite::sprite_sheets["dirt"]};

    return dirt_sheet;

}

bool Background::check_not_passable( std::string character )
{
    return (character == "null");
}
