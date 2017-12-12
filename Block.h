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
        Block();

        explicit Block(int depth, std::string object);
        void erase_block();

};

#endif