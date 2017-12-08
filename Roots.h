#ifndef ROOTS_H
#define ROOTS_H

#include "Block.h"

class Roots : Block
{

private:

    double slow_multiplier;

public:

    void animate() override;

};

#endif