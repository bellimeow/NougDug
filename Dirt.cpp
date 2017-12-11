//
// Created by seblu114 on 12/10/17.
//

#include "Dirt.h"

Dirt::Dirt( int depth )
        : Block( depth )
{
    texture.loadFromFile("/home/isade842/Documents/TDP005/NougDug/documents/Nougdug/deathp.png");
}

void Dirt::draw(sf::RenderWindow *window, int row, int column, const sf::Texture &my_texture) {

}

void Dirt::animate() {
    Sprite::animate();
}

sf::Texture Sprite::get_sprite_sheet()
{
    return *sprite_sheets["dirt"];
}
