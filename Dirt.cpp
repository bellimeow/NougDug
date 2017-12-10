//
// Created by seblu114 on 12/10/17.
//

#include "Dirt.h"

Dirt::Dirt( int depth )
        : Block( depth )
{
    texture.loadFromFile("/home/seblu114/TDP005/NougDug/documents/Nougdug/empty_tunnel.png");
}

void Dirt::animate()
{
    Sprite::animate();
}

void Dirt::draw( sf::RenderWindow * window, int row, int column, sf::Texture const &my_texture )
{
    Sprite::draw( window, row, column, texture);
}
