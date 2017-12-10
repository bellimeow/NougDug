//
// Created by seblu114 on 12/7/17.
//


#include <string>
#include "Sprite.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Sprite::Sprite(const std::string &sprite_sheet_path)
        : sprite_sheet_path(sprite_sheet_path)
{

}

void Sprite::draw(sf::RenderWindow* window_ptr, int row, int column, sf::Texture my_texture)
{

    //sf::Sprite sprite;
    sf::RectangleShape sprite{sf::Vector2f{16 * Game::DISPLAY_SIZE_MULTIPLIER, 16 * Game::DISPLAY_SIZE_MULTIPLIER}};
    //sprite.setFillColor(sf::Color::Blue);
    sprite.setTexture(&my_texture);
    //sprite.setScale(sf::Vector2f{16 * Game::DISPLAY_SIZE_MULTIPLIER, 16 * Game::DISPLAY_SIZE_MULTIPLIER});
    sprite.setPosition(sf::Vector2f((16*column*Game::DISPLAY_SIZE_MULTIPLIER), (16*row*Game::DISPLAY_SIZE_MULTIPLIER)));
    window_ptr->draw(sprite);
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

Sprite::Sprite()
{

}

void Sprite::set_position( int row, int column )
{

}

const sf::Texture &Sprite::getTexture() const
{
    return texture;
}
