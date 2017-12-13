//
// Created by seblu114 on 12/12/17.
//

#include "Rock.h"
#include "Dirt.h"



Rock::Rock( int depth )
        : Block( depth, "rock")
{
    texture = get_sprite_sheet();
}

void Rock::draw( sf::RenderWindow *window, int row, int column, sf::Sprite rock_sprite)
{
    sf::Sprite dirt_sprite;
    Dirt dirt(depth);

    dirt.draw(window, row, column, dirt_sprite);


    rock_sprite.setTexture(texture);
    rock_sprite.setTextureRect(Sprite::extract_texture_position(SpriteType::ROCK));

    Sprite::draw( window, row, column, rock_sprite);
}

void Rock::animate()
{
    Sprite::animate();
}

sf::Texture Rock::get_sprite_sheet()
{
    sf::Texture rock_sheet {*Sprite::sprite_sheets["rock"]};

    return rock_sheet;

}

bool Rock::check_passable(std::string character )
{
    return !(character == "player");
}

void Rock::set_position( int y, int x )
{
    current_position.y = y;
    current_position.x = x;
}

const std::string &Rock::get_i_am_a() const
{
    return i_am_a;
}