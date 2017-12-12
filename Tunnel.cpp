//
// Created by seblu114 on 12/12/17.
//

#include "Tunnel.h"

Tunnel::Tunnel( int depth )
        : Block( depth, "tunnel")
{
    texture = get_sprite_sheet();
}

void Tunnel::draw( sf::RenderWindow *window, int row, int column, sf::Sprite tunnel_sprite )
{
    std::map<int, SpriteType> tunnel_depth_map{
            {1, SpriteType::TUNNEL_D1_3}, {2, SpriteType::TUNNEL_D1_CORNER}, {3, SpriteType::TUNNEL_D1_2}, {4, SpriteType::TUNNEL_D1_1},
            {5, SpriteType::TUNNEL_D2_3}, {6, SpriteType::TUNNEL_D2_CORNER}, {7, SpriteType::TUNNEL_D2_2}, {8, SpriteType::TUNNEL_D2_1},
            {9, SpriteType::TUNNEL_D3_3}, {10, SpriteType::TUNNEL_D3_CORNER}, {11, SpriteType::TUNNEL_D3_2}, {12, SpriteType::TUNNEL_D3_1},
            {13, SpriteType::TUNNEL_D4_3}, {14, SpriteType::TUNNEL_D4_CORNER}, {15, SpriteType::TUNNEL_D4_2}, {16, SpriteType::TUNNEL_D4_1},
            {17, SpriteType::TUNNEL_4} };
//

    tunnel_sprite.setTexture(four_way);
    tunnel_sprite.setTextureRect(Sprite::extract_texture_position(tunnel_depth_map[1*depth]));

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

bool Tunnel::check_passable(std::string character)
{
    return !(character == "null");
}

void Tunnel::set_position( int y, int x )
{
    current_position.y = y;
    current_position.x = x;
}

const std::string &Tunnel::get_i_am_a() const
{
    return i_am_a;
}