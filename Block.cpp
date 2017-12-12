//
// Created by seblu114 on 12/7/17.
//

#include "Block.h"

void Block::erase_block()
{

}

Block::Block( int depth, std::string object )
    :depth{depth}, Sprite(object)
{

}

Block::Block() = default;
