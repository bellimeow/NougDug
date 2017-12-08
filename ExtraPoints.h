#ifndef XTRAPOINT_H
#define XTRAPOINT_H

#include "Block.h"

class ExtraPoints : Block
{

private:

    int points;

public:

    void animate() override;

};

#endif