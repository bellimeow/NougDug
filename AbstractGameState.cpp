

#include <iostream>
#include "AbstractGameState.h"
#include "SpritesType.h"
#include "Sprite.h"

const std::string AbstractGameState::sprite_sheet_path = "textures/";
int AbstractGameState::high_score;

std::map< std::string, sf::Texture*> AbstractGameState::sprite_sheets;

std::map< char, sf::IntRect > AbstractGameState::number_sprite_sheets;

void AbstractGameState::load_state_sheets()
{
    std::array< std::string, 5 > file_names
            {
                    "highscore", "noug", "start", "numbers", "lives"
            };

    for ( auto name( std::begin( file_names ) ); name < std::end( file_names );
          ++name )
    {
        sprite_sheets[ *name ] = new sf::Texture;

        if ( !sprite_sheets[ *name ]->
                loadFromFile( sprite_sheet_path + *name + ".png" ) )
        {
            std::cerr << "Couldn't open " + *name +
                    " sprite sheet file in AbstractGameState!" << std::endl;
        }
    }
}

void AbstractGameState::extract_number_textures()
{
    std::map< char, SpriteType > numbers{
            { '0', SpriteType::ZERO }, { '1', SpriteType::ONE }, { '2', SpriteType::TWO }, { '3', SpriteType::THREE },
            { '4', SpriteType::FOUR }, { '5', SpriteType::FIVE }, { '6', SpriteType::SIX }, { '7', SpriteType::SEVEN },
            { '8', SpriteType::EIGHT }, { '9', SpriteType::NINE } };

    for ( auto const &nr : numbers )
    {
        sf::IntRect sheet_rectangle{ Sprite::extract_texture_position( nr.second ) };

        number_sprite_sheets.insert( std::pair<char, sf::IntRect>( nr.first, sheet_rectangle ) );
    }
}

int AbstractGameState::get_high_score() const
{
    return AbstractGameState::high_score;
}

void AbstractGameState::set_high_score( int score )
{
    AbstractGameState::high_score += score;
}


