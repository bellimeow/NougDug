//
// Created by seblu114 on 12/13/17.
//

#include "Background.h"

Background::Background( int depth )
        : Block( depth, "background")
{
    texture = get_sprite_sheet();
}

void Background::draw( sf::RenderWindow * window, int row, int column,
                       sf::Sprite& background_sprite )
{
    if ( row == 0 && column == 0 );
    {
        background_sprite.setTexture( texture );
        background_sprite.setPosition( column, row );
        background_sprite.setScale( scale, scale );

         sf::Texture pumpkin;
        pumpkin.loadFromFile ("textures/pumpkin.png");
        sf::Sprite overlay;

        overlay.setTexture( pumpkin );
        overlay.setPosition( column, row+48 );
        overlay.setScale( scale, scale );

        window->draw( background_sprite );
        window->draw( overlay );
    }
}

sf::Texture Background::get_sprite_sheet()
{
    sf::Texture dirt_sheet { *Sprite::sprite_sheets[ "board_background" ] };

    return dirt_sheet;
}

bool Background::check_not_passable ( std::string character ) const
{
    return ( character == "null" );
}

void Background::animate()
{
    Sprite::animate();
}
