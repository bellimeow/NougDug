#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <map>
#include <SFML/System/Clock.hpp>
#include "PlayState.h"
#include "Sprite.h"
#include "Player.h"
#include "Character.h"

class PlayState;

struct block_test
{
    int height{};
    int width{};
};

class Board
{
    private:
        int const BACKGROUND_DEPTH;

        int enemy_count{};
        int rock_count{};
        std::vector<std::vector<Sprite*>> blocks;
        std::vector<std::vector<Sprite*>> characters;
        Sprite* player;
        PlayState* update_playstate{};
        sf::Clock time{};
        std::map<int, int> depth_levels{   {1, 0},
                                           {2, 0},
                                           {3, 0},
                                           {4, 0}   };

        void check_collision();
        bool check_collision_simple();
        bool rock_proximity();
        bool projectile_collide();
        bool rock_crush();
        bool wall();
        bool dig();
        bool collision_with_enemy();
        bool immovable_object();
        int calculate_score();
        void insert_objects(std::ifstream* ifs);
        void set_board_size(std::vector<std::vector<Sprite*>>& object_vector, const unsigned int width, const unsigned int height);

    public:

        Board(std::ifstream*, int width, int height, PlayState* ps);

        std::unordered_map<char, Sprite* (*)(int)> create_block_function_map();
        std::unordered_map<char, Sprite* (*)(void)> create_character_function_map();
        void player_action(std::string);
        void set_depth_levels();
        int check_depth_level (int const);
        static Sprite* create_dirt(int);
        static Sprite* create_tunnel(int);
        static Sprite* create_rock(int);
        //static Sprite* create_root(int);
        //static Sprite* create_extra_points(int);
        static Sprite* create_background(int);
};

#endif