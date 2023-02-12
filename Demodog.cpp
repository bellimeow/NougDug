//
// Created by seblu114 on 12/12/17.
//

#include "Demodog.h"

Demodog::Demodog()
        : Enemies(3, "demodog", 10)
{
    texture = get_sprite_sheet();
}

void Demodog::draw( sf::RenderWindow *window, int row, int column, sf::Sprite& enemy_sprite )
{
    std::map<int, SpriteType> demodog_map{
            {1, SpriteType::FRONT}, {2, SpriteType::FRONT_R_FOOT}, {3, SpriteType::FRONT_L_FOOT}, {4, SpriteType::WIN},
            {5, SpriteType::RIGHT}, {6, SpriteType::RIGHT_R_FOOT}, {7, SpriteType::RIGHT_L_FOOT},
            {8, SpriteType::LEFT},  {9, SpriteType::LEFT_R_FOOT},  {10, SpriteType::LEFT_L_FOOT},
            {11, SpriteType::BACK}, {12, SpriteType::BACK_R_FOOT}, {13, SpriteType::BACK_L_FOOT}, {14, SpriteType::DEATH},
            {15, SpriteType::GHOST_FRONT}, {16, SpriteType::GHOST_FRONT_2}};

    enemy_sprite.setTexture(texture);


    if ( pumped > 0 )
    {
        enemy_sprite.setTextureRect( Sprite::extract_texture_position( demodog_map[4] ));
    }
    else if ( ghost_hunting )
    {
        enemy_sprite.setTexture(demodog_ghost_sheet);
        enemy_sprite.setTextureRect( Sprite::extract_texture_position( demodog_map[15] ) );
    }
    else if (is_alive)
    {
        enemy_sprite.setTextureRect( Sprite::extract_texture_position( demodog_map[1] ));
    }
    else
    {
        enemy_sprite.setTextureRect( Sprite::extract_texture_position( demodog_map[14] ));
    }

    Sprite::draw( window, row, column, enemy_sprite);
}

sf::Texture Demodog::get_sprite_sheet()
{
    sf::Texture demodog_sheet {*Sprite::sprite_sheets["demodog"]};
    demodog_ghost_sheet = *Sprite::sprite_sheets["ghost"];

    return demodog_sheet;
}

void Demodog::animate()
{
    Sprite::animate();
}


bool Demodog::check_not_passable( std::string object ) const
{
    return (object == "rock" || object == "nougat");
}
