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
#include "Rock.h"
#include "Tunnel.h"
#include "Demodog.h"

typedef Sprite* (*BlockFunction)(int);
typedef std::unordered_map<char, BlockFunction> BlockFunctionMap;

typedef Sprite* (*CharacterFunction)(void);
typedef std::unordered_map<char, CharacterFunction> CharacterFunctionMap;

Board::Board(std::ifstream* game_board, const int width, const int height, PlayState* ps, sf::RenderWindow* window)
    : BACKGROUND_DEPTH{3}, update_playstate{ps}, window_ptr{window}
{
    set_board_size(blocks, width, height);
    set_board_size(characters, width, height);

    set_depth_levels();

    Sprite::load_sprite_sheets();

    insert_objects(game_board);
}

void Board::check_collision()
{
    //check_passable
    //check_dig
    //collision_with_enemy
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

bool Board::dig() {
    return false;
}

void Board::check_tunnel(sf::Vector2i position)
{
    //blocks[position.y][position.x]->get_adjacent_tunnels();
}

bool Board::collision_with_enemy() {
    return false;
}

bool Board::check_passable(sf::Vector2i passing_object_pos, sf::Vector2i object_pos) {

    std::string passing_object_type {characters[passing_object_pos.y][passing_object_pos.x]->get_i_am_a()};


    return blocks[object_pos.y][object_pos.x]->check_passable(passing_object_type);
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
    //func.emplace('&', &create_root);
    //func.emplace('X', &create_extra_points);
    func.emplace('B', &create_background);

    return func;
}

CharacterFunctionMap Board::create_character_function_map()
{
    CharacterFunctionMap func;
    func.emplace('@', &create_player);
    func.emplace('=', &create_demodog);

    //func.emplace('#', &Board::create_demogorgon);

    return func;
}

void Board::insert_objects( std::ifstream* ifs)

{
    std::cout << "Insert Object" << "\n";
    BlockFunctionMap block_map{create_block_function_map()};
    CharacterFunctionMap character_map{create_character_function_map()};

    char obj_char;

    int depth_level {1};

    for (int row = 0; row < blocks.size(); ++row)
    {
        depth_level = check_depth_level(row);

        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            while( ifs->get(obj_char) ) {

                std::cout << obj_char << "\n";
                if (block_map.count(obj_char) > 0)
                {
                    BlockFunction function = block_map[obj_char];
                    blocks[row][column] = (*function)(depth_level);
                    break;
                }
                else if (character_map.count(obj_char) > 0)
                {
                    CharacterFunction function = character_map[obj_char];
                    characters[row][column] = (*function)();
                    blocks[row][column] = create_tunnel(depth_level);
                    characters[row][column]->set_position(row, column);

                    if (obj_char == '@')
                    {
                        player = reinterpret_cast<Player*>(characters[row][column]);
                        player->set_position(row, column);
                    }
                    break;
                }
                else if ( obj_char != '|' && obj_char != '\n' )
                {
                    break;
                }
            }
        }
    }
}

void Board::set_board_size(std::vector<std::vector<Sprite*>> &object_vector, const unsigned int width, const unsigned int height)
{
    Sprite* null{nullptr};

    object_vector.resize(height);
    for (auto row = object_vector.begin(); row != object_vector.end(); ++row) {
        (*row).resize(width);
        std::fill((*row).begin(), (*row).end(), null);
    }
}

void Board::set_depth_levels()
{
    unsigned int height {update_playstate->board_height};

    int board_dirt_size {height-BACKGROUND_DEPTH};

    int depth {board_dirt_size/4};

    int rest{board_dirt_size % 4};

    depth_levels[1] = BACKGROUND_DEPTH ;

    for (int i{ 2 }; i < 5; ++i)
    {
        depth_levels[i] = depth_levels[i-1] + depth;

        if ( rest > 0)
        {
            depth_levels[i] += 1;
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
    else if (depth_levels[2] <= row && row < depth_levels[3])
    {
        return 2;
    }
    else if (depth_levels[3] <= row && row < depth_levels[4])
    {
        return 3;
    }
    else if (depth_levels[4] <= row)
    {
        return 4;
    }
    return 0;
}


void Board::draw()
{
    for (int row = 0; row < blocks.size(); ++row)
    {
        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            sf::Sprite sprite;
            if (blocks[row][column] != nullptr ) {
                blocks[row][column]->draw( window_ptr, row, column, sprite );
            }
            if (characters[row][column] != nullptr)
            {
                characters[row][column]->draw( window_ptr, row, column, sprite);
            }
        }
    }
}

/*Sprite* Board::create_root(int depth)
{
    return new Root(depth);
}*/

Sprite* Board::create_dirt(int depth)
{
    return new Dirt(depth);
}

Sprite* Board::create_tunnel(int depth)
{
    return new Tunnel(depth);
    //return nullptr;
}

Sprite* Board::create_rock(int depth)
{
    return new Rock(depth);
    //return nullptr;
}

/*Sprite* Board::create_extra_points(int depth)
{
    return new ExtraPoints(depth);
}*/

Sprite* Board::create_background(int depth)
{
    //return new Block(depth);
    return nullptr;
}

void Board::player_action( std::string action )
{
    if (action == "shoot" || action == "place")
    {
    }
    else
    {
        sf::Vector2i player_pos {player->get_current_x(), player->get_current_y()};

        std::map<std::string, sf::Vector2i> direction_values{ {"up",    {0, -1}},
                                                              {"right", {1, 0 }},
                                                              {"down",  {0, 1 }},
                                                              {"left",  {-1, 0}} };

        if ( ( action == "right" && player_pos.x < update_playstate->board_width - 1 ) ||
             ( action == "left" && player_pos.x > 0 ) ||
             ( action == "up" && player_pos.y > BACKGROUND_DEPTH - 1 ) ||
             ( action == "down" && player_pos.y < update_playstate->board_height - 1 ) )
        {
            moving_character(direction_values[action].x, direction_values[action].y, player_pos);
        }

        //player->animate();
    }
}

void Board::moving_character(int x_add, int y_add, sf::Vector2i character_pos)
{
    Sprite* temp;

    //collision check

    temp = characters[character_pos.y + y_add][character_pos.x + x_add];
    characters[character_pos.y + y_add][character_pos.x + x_add] = player;
    characters[character_pos.y][character_pos.x] = temp;

    player->set_position(character_pos.y + y_add, character_pos.x + x_add);
}


Sprite *Board::create_player()
{
    return new Player();
}

Sprite *Board::create_demodog()
{
    return new Demodog();
}

std::array<Sprite*, 5> Board::get_adjacent_objects( sf::Vector2i mid_pos)
{
    return std::array<Sprite*, 5>();
}
