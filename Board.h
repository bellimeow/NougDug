#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include "PlayState.h"
#include "Sprite.h"

class PlayState;

struct block_test
{
    int height{};
    int width{};
};

struct enemy_test
{
    int height{};
    int width{};
};

class Board
{
    private:
        int const BACKGROUND_DEPTH{3};

        int enemy_count{};
        int rock_count{};
        std::vector<std::vector<block_test>> blocks;
        std::vector<std::vector<enemy_test>> characters;
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
        void insert_objects(std::vector object_vector, std::ifstream* ifs, std::string vector_type);
        void insert_characters(std::vector object_vector, std::ifstream* ifs);
        void set_board_size(std::vector& object_vector, int width, int height);

    public:

        Board(std::ifstream*, int width, int height);

        std::unordered_map<char, void (*)(int)> create_block_function_map();
        std::unordered_map<char, void (*)(void)> create_character_function_map();
        void set_depth_levels();
        int check_depth_level (int const);
        Sprite* create_dirt(int);
        Sprite* create_tunnel(int);
        Sprite* create_rock(int);
        //Sprite* create_root(int);
        //Sprite* create_extra_points(int);
        Sprite* create_background(int);
};

#endif