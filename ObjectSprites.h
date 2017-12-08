#ifndef OBJECT_SPRITE_H
#define OBJECT_SPRITE_H

/*
 * | 0 | 1 | 2 | 3 |
 * | 4 | 5 | 6 | 7 |
 * | 8 | 9 |10 |11 |
 * |12 |13 |14 |15 |
 *
 * Hur sprites är ordnade i en fil.
 */

enum class ObjectType
{
    FRONT, FRONT_R_FOOT, FRONT_L_FOOT, WIN,
    RIGHT, RIGHT_R_FOOT, RIGHT_l_FOOT,
    LEFT, LEFT_R_FOOT, LEFT_L_FOOT,
    BACK, BACK_R_FOOT, BACK_L_FOOT, DEATH,

    DIRT_DEPTH_1, DIRT_DEPTH_2, DIRT_DEPTH_3, DIRT_DEPTH_4,

    TUNNEL_4, TUNNEL_CORNER, TUNNEL_2, TUNNEL_1,

    ROCK,

    NOUGAT,

    ROOTS_1, ROOTS_2, ROOTS_3, ROOTS_4,

    EXTRA_POINT,
};


#endif
