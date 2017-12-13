//
// Created by isade842 on 12/8/17.
//

#include "Nougat.h"

sf::Texture Nougat::get_sprite_sheet() {
    sf::Texture nougat_sheet {*Sprite::sprite_sheets["nougat"]};

    return nougat_sheet;
}
