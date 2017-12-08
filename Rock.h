#ifndef ROOTS_H
#define ROOTS_H

#include "Block.h"

class Rock : Block
{

private:

    bool is_falling;

public:

    void animate() override;

};

#endif