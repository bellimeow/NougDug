//
// Created by seblu114 on 12/6/17.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "Board.h"
#include "Dirt.h"

typedef void (*BlockFunction)(int);
typedef std::unordered_map<char, BlockFunction> BlockFunctionMap;

typedef void (*CharacterFunction)(void);
typedef std::unordered_map<char, CharacterFunction> CharacterFunctionMap;

Board::Board(std::ifstream* game_board, const int width, const int height)
{
    set_board_size(blocks, width, height);
    set_board_size(characters, width, height);

    set_depth_levels();

    insert_objects(blocks, game_board, "Blocks");
    insert_characters(characters, game_board);
}

void Board::check_collision() {

}

bool Board::check_collision_simple() {
    return false;
}

bool Board::rock_proximity() {
    return false;
}

bool Board::projectile_collide() {
    return false;
}

bool Board::rock_crush() {
    return false;
}

bool Board::wall() {
    return false;
}

bool Board::dig() {
    return false;
}

bool Board::collision_with_enemy() {
    return false;
}

bool Board::immovable_object() {
    return false;
}

int Board::calculate_score() {
    return 0;
}



BlockFunctionMap Board::create_block_function_map()
{
    BlockFunctionMap func;
    func.emplace('D', &create_dirt);
    func.emplace('T', &create_tunnel);
    func.emplace('R', &create_rock);
    func.emplace('@', &create_tunnel);
    func.emplace('=', &create_tunnel);
    func.emplace('#', &create_tunnel);
    //func.emplace('&', &create_root);
    //func.emplace('X', &create_extra_points);
    func.emplace('B', &create_background);

    //ScriptFunction x;
    //(*x)();

    //std::function<void (void)> x;
    //x(...);

    return func;
}

CharacterFunctionMap Board::create_character_function_map()
{
    //HUr kommer specifik sprite ritas ut?
    CharacterFunctionMap func;
    func.emplace('@', &create_player);
    func.emplace('=', &create_demodog);
    func.emplace('#', &create_demogorgon);

    return func;
}

void Board::insert_objects( std::vector object_vector, std::ifstream* ifs, std::string vector_type )
{
    std::unordered_map functions;

    if ( vector_type == "Blocks" )
    {
        functions = create_block_function_map();
    }
    else if ( vector_type == "Characters" )
    {
        functions = create_character_function_map();
    }

    char obj_char;

    int depth_level {1};

    for (int row = 0; row < object_vector.size(); ++row)
    {
        depth_level = check_depth_level(row);

        for (int column = 0; column < object_vector[row].size() ; ++column)
        {
            while( ifs->get(obj_char) ) {

                if (functions[obj_char] && vector_type == "Blocks")
                {
                    BlockFunction function = functions[obj_char];
                    object_vector[row][column] = (*function)(depth_level);
                }
                else if (functions[obj_char] && vector_type == "Character")
                {
                    CharacterFunction function = functions[obj_char];
                    object_vector[row][column] = (*function)();
                }
                else if ( obj_char != '|' && obj_char != '\n' )
                {
                    break;
                }
            }
        }
    }
}

void Board::set_board_size(std::vector &object_vector, int width, int height)
{
    object_vector.resize(height);
    std::for_each(object_vector.begin(), object_vector.end(), object_vector.resize(width));
}

void Board::set_depth_levels()
{
    int height {update_playstate->board_height};

    int board_dirt_size {height-BACKGROUND_DEPTH};

    int depth {board_dirt_size/4};

    depth_levels[1] = BACKGROUND_DEPTH ;
    depth_levels[2] = depth_levels[1] + depth;
    depth_levels[3] = depth_levels[2] + depth;
    depth_levels[4] = depth_levels[3] + depth;

    int rest{board_dirt_size % 4};

    if (rest != 0)
    {
        for (int level = 1; rest > 0 ; ++level)
        {
            depth_levels[level] += 1;
            --rest;
        }
    }
}

int Board::check_depth_level(int const row)
{
    if ( depth_levels[1] <= row && row < depth_levels[2])
    {
        return 1;
    }
    else if (depth_levels[2] <= row < depth_levels[3])
    {
        return 2;
    }
    else if (depth_levels[3] <= row < depth_levels[4])
    {
        return 3;
    }
    else if (depth_levels[4] <= row)
    {
        return 4;
    }
    return 0;
}

Sprite* Board::create_dirt(int depth)
{
    return new Dirt(depth);
}

Sprite* Board::create_tunnel(int depth)
{
    return new Tunnel(depth);
}

Sprite* Board::create_rock(int depth)
{
    return new Rock(depth);
}

/*Sprite* Board::create_root(int depth)
{
    return new Root(depth);
}*/

/*Sprite* Board::create_extra_points(int depth)
{
    return new ExtraPoints(depth);
}*/

Sprite* Board::create_background(int depth)
{
    return new Block(depth);
}
