//
// Created by seblu114 on 12/6/17.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <bits/unordered_map.h>
#include "Board.h"

typedef void (*ScriptFunction)(void);
typedef std::unordered_map<char, ScriptFunction> ScriptMap;

Board::Board(std::string const &filename) {
    std::ifstream level_data;
    level_data.open(filename, std::ifstream::in);

    if ( level_data.fail() )
    {
        std::cerr << "Couldn't open file!\n";
    }
    else
    {
        std::ifstream* level_ptr{&level_data};
        level_data >> board_height >> board_width;
        std::cout << board_height << " " << board_width << "\n";

        insert_objects(blocks, level_ptr);

        std::cout << blocks[0][0].height << " " << blocks[0][1].height << " " << blocks[0][15].height << "\n";
    }
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

ScriptMap Board::create_function_map()
{
    ScriptMap func;
    func.emplace('1', &);
    func.emplace('2', &);
    func.emplace('3', &);
    func.emplace('4', &);
    func.emplace('T', &);
    func.emplace('R', &);
    func.emplace('&', &);
    func.emplace('X', &);
    func.emplace('B', &create_block);

    //ScriptFunction x;
    //(*x)();

    //std::function<void (void)> x;
    //x(...);

    return func;
}

void Board::insert_objects( std::array<std::array<block_test, 16>, 18> object_array, std::ifstream* ifs)
{
    char block_char;
    std::map<char, Block*>

    std::for_each( std::begin(object_array), std::end(object_array), [this, &ifs, &block_char](auto row){
        std::for_each( std::begin(row), std::end(row),
                       [&ifs, &block_char](auto position)
        {
           while( ifs->get(block_char) ) {

           }
       } );
    } );


}

void Board::insert_characters( std::array<std::array<block_test, 16>, 18> object_array, std::ifstream ifs)
{
    char block_char;

    std::for_each( std::begin(object_array), std::end(object_array), [this, &ifs, &block_char](auto row){
        std::for_each( std::begin(row), std::end(row),
                       [&ifs, &block_char](auto width)
                       {
                           while( ifs >> block_char )
                           {
                               switch (block_char)
                               {
                                   case '@':
                                       std::cout << "Player";
                                       break;

                                   case '=':
                                       std::cout << "Demodog";
                                       break;

                                   case '#':
                                       std::cout << "Demogorgon";
                                       break;

                                   case '|':
                                       std::cout << " ";
                                   default:
                                       std::cout << "";
                               }
                           }

                       } );
    } );


}
