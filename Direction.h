#ifndef TEXTURE_H
#define TEXTURE_H

/*
 * | 0 | 1 | 2 | 3 |
 * | 4 | 5 | 6 | 7 |
 * | 8 | 9 |10 |11 |
 * |12 |13 |14 |15 |
 *
 * Hur sprites är ordnade i en fil.
 */


enum class Texture
{
    FRONT = 0, FRONT_R_FOOT, FRONT_L_FOOT, WIN,
    RIGHT, RIGHT_R_FOOT, RIGHT_l_FOOT,
    LEFT, LEFT_R_FOOT, LEFT_L_FOOT,
    BACK, BACK_R_FOOT, BACK_L_FOOT, DEATH,

    DIRT_1, DIRT_2, DIRT_3, DIRT_4,

    TUNNEL_4, TUNNEL_CORNER, TUNNEL_2

};


#endif
