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
    tunnel_sprite.setTextureRect(Sprite::extract_texture_position(tunnel_depth_map[1/**depth*/]));

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

bool Tunnel::check_not_passable(std::string character)
{
    return (character == "null");
}

void Tunnel::get_tunnels(  std::array<std::array<Sprite*, 3>, 3> tunnels )
{
    std::array<sf::Vector2i, 4> array_positions{ (0,1), (1,0), (1,2), (2,1) };

    int count{0};

    for (int i = 0; i < array_positions.size(); ++i)
    {
        if(tunnels[array_positions[i].y][array_positions[i].x]->get_i_am_a() == i_am_a)
        {
            ++count;
        }
    }

    if (count == 2)
    {
        check_two_way_type(tunnels);
    }
    else
    {
        get_tunnel_type(tunnels, count);
    }

    get_tunnel_type(count);
}

void Tunnel::get_rotation(std::array<std::array<Sprite*, 3>, 3> tunnels)
{
 // container med rotationsgrader
}

void Tunnel::get_tunnel_type( std::array<std::array<Sprite*, 3>, 3> tunnels, int count )
{
    if (count == 0 || count == 4)
    {
        current_texture = 17;
    }
    else if (count == 1)
    {
        current_texture = 4;
    }
    else if(count == 3)
    {
        current_texture = 1;
    }

}

void Tunnel::check_two_way_type( std::array<std::array<Sprite*, 3>, 3> tunnels )
{
    if (tunnels[1][0]->get_i_am_a() == i_am_a && tunnels[1][2]->get_i_am_a() == i_am_a)
    {
        current_texture = 3;
        rotation_value = 0;
    }
    else if (tunnels[0][1]->get_i_am_a() == i_am_a && tunnels[2][1]->get_i_am_a() == i_am_a )
    {
        current_texture = 3;
        rotation_value = 90;
    }
    else if (tunnels[1][0]->get_i_am_a() == i_am_a && tunnels[2][1]->get_i_am_a() == i_am_a)
    {
        current_texture = 2;
        rotation_value = 0;
    }
    else if (tunnels[0][1]->get_i_am_a() == i_am_a && tunnels[1][0]->get_i_am_a() == i_am_a)
    {
        current_texture = 2;
        rotation_value = 90;
    }
    else if (tunnels[1][2]->get_i_am_a() == i_am_a && tunnels[0][1]->get_i_am_a() == i_am_a)
    {
        current_texture = 2;
        rotation_value = 180;
    }
    else if (tunnels[2][1]->get_i_am_a() == i_am_a && tunnels[1][2]->get_i_am_a() == i_am_a)
    {
        current_texture = 2;
        rotation_value = 270;
    }

}

