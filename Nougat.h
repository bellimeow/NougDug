//
// Created by isade842 on 12/8/17.
//

#ifndef NOUGDUG_NOUGAT_H
#define NOUGDUG_NOUGAT_H


#include "Sprite.h"

class Nougat : Sprite
{
    private:
    sf::Texture Sprite::get_sprite_sheet()
    {
        return *sprite_sheets["dirt"];
    }


};


#endif //NOUGDUG_NOUGAT_H
