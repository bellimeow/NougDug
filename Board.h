#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>
#include <SFML/System/Clock.hpp>
#include "PlayState.h"

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
        unsigned int board_width{};
        unsigned int board_height{};
        int enemy_count{};
        int rock_count{};
        std::array<std::array<block_test, 16>, 18> blocks;
        std::array<std::array<enemy_test, 16>, 18> characters;
        PlayState* update_playstate{};
        sf::Clock time{};

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
        void insert_objects(std::array<std::array<block_test, 16>, 18> object_array, std::ifstream* ifs);

    public:
        Board(std::string const &filename);

    void insert_characters(std::array<std::array<block_test, 16>, 18> object_array, std::ifstream ifs);

    std::unordered_map<char, void (*)(void)> create_function_map();
};

#endif