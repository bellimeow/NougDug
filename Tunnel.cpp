//
// Created by seblu114 on 12/12/17.
//

#include "Tunnel.h"

Tunnel::Tunnel( int depth )
        : Block( depth )
{
    texture = get_sprite_sheet();
}

void Tunnel::draw( sf::RenderWindow *window, int row, int column, sf::Sprite tunnel_sprite )
{
    std::map<int, SpriteType> tunnel_depth_map{ {1, SpriteType::DIRT_DEPTH_1},
                                              {2, SpriteType::DIRT_DEPTH_2},
                                              {3, SpriteType::DIRT_DEPTH_3},
                                              {4, SpriteType::DIRT_DEPTH_4} };

    tunnel_sprite.setTexture(four_way);
    tunnel_sprite.setTextureRect(Sprite::extract_texture_position(tunnel_depth_map[1]));

    Sprite::draw( window, row, column, tunnel_sprite);;
}

void Tunnel::animate()
{
    Sprite::animate();
}

sf::Texture Tunnel::get_sprite_sheet()
{
    sf::Texture tunnel_sheet {*Sprite::sprite_sheets["tunnel"]};
    four_way = *Sprite::sprite_sheets["tunnel4"];

    return tunnel_sheet;
}

