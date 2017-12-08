//
// Created by seblu114 on 12/7/17.
//


#include <string>
#include "Sprite.h"
#include <SFML/Graphics.hpp>

Sprite::Sprite()
{

}

void Sprite::draw()
{
    sf::Sprite sprite;
    sprite.setTexture(*sprite_sheets["player"]);
}

sf::Texture Sprite::get_sprite_sheet(std::string path)
{

}

void Sprite::animate()
{

}


void Sprite::load_sprite_sheets()
{
    sf::Texture player_sprite_sheet;
    if (!player_sprite_sheet.loadFromFile(sprite_sheet_path + "deathp.png" ))
    {
        sprite_sheets.insert(std::pair<std::string, sf::Texture*>("player", &player_sprite_sheet));
    }


}