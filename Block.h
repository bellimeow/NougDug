#ifndef BLOCK_H
#define BLOCK_H

#include "Sprite.h"

class Block : Sprite
{

    protected:
        int width;
        int height;
        int depth;

    public:
        void erase_block();

};

#endif