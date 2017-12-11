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

void Dirt::draw( sf::RenderWindow * window, int row, int column)
{
    Sprite::draw( window, row, column);
}

sf::Texture Dirt::get_sprite_sheet()
{
    //sf::Texture sprite_sheet{ sprite_sheets["Dirt"] };

}
