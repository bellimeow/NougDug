#ifndef BLOCK_H
#define BLOCK_H

#include "Sprite.h"

/**
 *  The block class is a subclass for Sprite and a base class for the different
 *  blocks, these are, Background, Dirt, Rock, Tunnel.
 **/

class Block : public Sprite
{

    protected:
        int width;
        int height;
        int depth;

    public:

        /// Default constructor
        Block();

        /// Constructor taking depth and a string for i_am_a
        explicit Block(int depth, std::string object);

        /// unused
        void erase_block();

        /// getter, depth
        int get_depth() const;
};

#endif