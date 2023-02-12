#ifndef SPRITETYPE_H
#define SPRITETYPE_H


/**
 * Enum Class to help keep track of positions i spritesheets
 */
enum class SpriteType
{
        FRONT, FRONT_R_FOOT, FRONT_L_FOOT, WIN,
        RIGHT, RIGHT_R_FOOT, RIGHT_L_FOOT, RIGHT_R_FOOT_2,
        LEFT,  LEFT_R_FOOT,  LEFT_L_FOOT, LEFT_R_FOOT_2,
        BACK,  BACK_R_FOOT,  BACK_L_FOOT,  DEATH,

        DIRT_DEPTH_1, DIRT_DEPTH_2, DIRT_DEPTH_3, DIRT_DEPTH_4,

        TUNNEL_4,

        TUNNEL_D1_3, TUNNEL_D1_CORNER, TUNNEL_D1_2, TUNNEL_D1_1,
        TUNNEL_D2_3, TUNNEL_D2_CORNER, TUNNEL_D2_2, TUNNEL_D2_1,
        TUNNEL_D3_3, TUNNEL_D3_CORNER, TUNNEL_D3_2, TUNNEL_D3_1,
        TUNNEL_D4_3, TUNNEL_D4_CORNER, TUNNEL_D4_2, TUNNEL_D4_1,

        ROCK,

        NOUGAT,

        ROOTS_1, ROOTS_2, ROOTS_3, ROOTS_4,

        EXTRA_POINT,

        PROJECTILE,

        ZERO, ONE, TWO, THREE,
        FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE,

        HIGHSCORE,

        HEART, EMPTY_HEART,

        GHOST_FRONT, GHOST_FRONT_2
};


#endif
