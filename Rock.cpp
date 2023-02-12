//
// Created by seblu114 on 12/12/17.
//

#include <cmath>
#include "Rock.h"
#include "Dirt.h"



Rock::Rock( int depth )
        : Block( depth, "rock")
{
    texture = get_sprite_sheet();
}

void Rock::draw( sf::RenderWindow *window, int row, int column, sf::Sprite& rock_sprite)
{
    rock_sprite.setTexture(texture);
    rock_sprite.setTextureRect(Sprite::extract_texture_position(SpriteType::ROCK));

    if ( is_falling() )
    {
        rock_sprite.setPosition(column, row);
        rock_sprite.setScale(scale, scale);

        window->draw( rock_sprite );
    }
    else
    {
        sf::Sprite dirt_sprite;
        Dirt dirt( depth );

        dirt.draw( window, row, column, dirt_sprite );

        Sprite::draw( window, row, column, rock_sprite );
    }
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

void Rock::move()
{
    ++real_position.y;

    set_position( static_cast<int>(std::round( real_position.y / (16*Game::DISPLAY_SIZE_MULTIPLIER ) )), get_current_x() );
}

bool Rock::check_not_passable(std::string character ) const
{
    return ( character == "player" || character == "nougat" || character == "demodog" );
}

bool Rock::is_falling() const
{
    return falling;
}

void Rock::set_falling( bool falling )
{
    Rock::falling = falling;
}

const sf::Vector2i &Rock::get_start_position() const
{
    return start_position;
}

void Rock::set_start_position( const sf::Vector2i &start_position )
{
    Rock::start_position = start_position;
}
