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
#include "Enemies.h"

class PlayState;

class Board
{
    private:
        int const BACKGROUND_DEPTH;

        int enemy_count{};
        int rock_count{};
        std::vector<std::vector<Sprite*>> blocks;
        std::vector<std::vector<Sprite*>> characters;
        sf::RenderWindow* window_ptr;
        Player* player;
        std::vector<Enemies*> enemies;
        PlayState* update_playstate{};
        sf::Clock time{};
        std::map<int, int> depth_levels{   {1, 0},
                                           {2, 0},
                                           {3, 0},
                                           {4, 0}   };
        int last_time;

        std::array<std::array<Sprite*, 3>, 3> get_adjacent_objects(sf::Vector2i mid_pos);
        bool check_collision(sf::Vector2i from, sf::Vector2i to);
        bool check_collision_simple();
        bool rock_proximity();
        bool projectile_collide();
        bool rock_crush();
        bool cant_dig(sf::Vector2i to);
        bool collision_with_enemy();
        bool check_not_passable( sf::Vector2i passing_object_pos, sf::Vector2i object_pos );
        int calculate_score();
        void insert_objects(std::ifstream* ifs);
        void set_board_size(std::vector<std::vector<Sprite*>>& object_vector, const unsigned int width, const unsigned int height);
        void moving_character(int x_add, int y_add, sf::Vector2i character_pos);
        void dig (sf::Vector2i position);

        static Sprite* create_dirt(int);
        static Sprite* create_tunnel(int);
        static Sprite* create_rock(int);
        //static Sprite* create_root(int);
        //static Sprite* create_extra_points(int);
        static Sprite* create_background(int);
        static Sprite* create_player();
        static Sprite* create_demodog();
        //static Sprite* create_player();
        void initialize_tunnels();

    public:



        Board(std::ifstream* game_board, int width, int height, PlayState* ps, sf::RenderWindow* window);

        std::unordered_map<char, Sprite* (*)(int)> create_block_function_map();

        std::unordered_map<char, Sprite* (*)(void)> create_character_function_map();
        void player_action(std::string);
        void draw();
        void set_depth_levels();
        void check_tunnel (sf::Vector2i position);
        int check_depth_level (int const);

};

#endif