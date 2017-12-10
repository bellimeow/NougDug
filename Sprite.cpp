//
// Created by seblu114 on 12/7/17.
//


#include <string>
#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const std::string Sprite::sprite_sheet_path = "/home/isade842/Documents/TDP005/NougDug/documents/Nougdug";

Sprite::Sprite(const std::string &sprite_sheet_path)
        : sprite_sheet_path(sprite_sheet_path)
{

}

sf::Sprite Sprite::draw()
{
    sf::Sprite sprite;
    sprite.setTexture(*sprite_sheets["player"]);
    return sprite;
}

sf::Texture Sprite::get_sprite_sheet(std::string path)
{

}

void Sprite::animate()
{

}


void Sprite::load_sprite_sheets()
{
    std::array file_names<std::string>{ "player","demodog","demogorgon",
                                        "dirt","tunnel","rock",
                                        "nougat","roots", "extra_points",
                                        "projectile"};

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
