//
// Created by isade842 on 12/8/17.
//

#include "Nougat.h"

Nougat::Nougat( const std::string &direction)
    : direction{direction}, Sprite( "nougat" )
{
    texture = get_sprite_sheet();
}

sf::Texture Nougat::get_sprite_sheet() {
    sf::Texture nougat_sheet {*Sprite::sprite_sheets["nougat"]};

    return nougat_sheet;
}

void Nougat::draw( sf::RenderWindow *window, int row, int column, sf::Sprite &noug_sprite )
{
    set_rotation(direction);
    std::map<std::string, sf::Vector2i> position_mod{ {"up", {8, 6}},
                                                      {"right", {6, 1 }},
                                                      {"down", {7, 12}},
                                                      {"left", {2, 8}} };

    int position_x { column + position_mod[direction].x * Game::DISPLAY_SIZE_MULTIPLIER };
    int position_y { row + position_mod[direction].y  * Game::DISPLAY_SIZE_MULTIPLIER };

    noug_sprite.setTexture( texture );
    noug_sprite.setScale(sf::Vector2f{Game::DISPLAY_SIZE_MULTIPLIER, Game::DISPLAY_SIZE_MULTIPLIER});

    if ( direction != "right" )
    {
        noug_sprite.setRotation( rotation_value );
        noug_sprite.setOrigin( 8, 8 );
    }

    noug_sprite.move(sf::Vector2f( position_x, position_y ));

    window->draw( noug_sprite );
}

bool Nougat::check_not_passable( std::string character ) const
{
    return (character == "demodog" || character == "demogorgon");
}

void Nougat::animate()
{
    Sprite::animate();
}

void Nougat::move()
{
    std::map<std::string, sf::Vector2i> direction_values{ {"up",    {0, -1}},
                                                          {"right", {1, 0 }},
                                                          {"down",  {0, 1 }},
                                                          {"left",  {-1, 0}} };

    real_position += direction_values[direction];
    set_rotation(direction);
}

void Nougat::set_rotation( std::string direction)
{
    std::map< std::string, int > rotation { {"up", 270},
                                            {"right", 0},
                                            {"down", 90},
                                            {"left",180}, };

    rotation_value = rotation[direction];
}

const sf::Vector2i &Nougat::get_start_position() const
{
    return start_position;
}

void Nougat::set_start_position( const sf::Vector2i &start_position )
{
    Nougat::start_position = start_position;
}

const std::string &Nougat::get_direction() const {
    return direction;
}

