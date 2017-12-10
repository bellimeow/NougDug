#ifndef BLOCK_H
#define BLOCK_H

#include "Sprite.h"

class Block : public Sprite
{

    protected:
        int width;
        int height;
        int depth;

    public:

        Block(int depth);
        void erase_block();

};

#endif