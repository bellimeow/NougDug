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
#include "Background.h"

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

bool Board::check_collision(sf::Vector2i from, sf::Vector2i to)
{
    if ( check_not_passable( from, to ) )
    {
        if ( cant_dig(to) )
        {
            return true;
        }
        dig(to);
    }
    return false;
    //collision_with_enemy
}

bool Board::check_collision_simple() {
    return false;
}

/*bool AABB::intersect(AABB const &a) const
{
    // bra!
    return ((a.left <= right) && (a.right >= left)) &&
           ( (a.top <= bottom) && (a.bottom >= top));
}*/

bool Board::rock_proximity() {
    return false;
}

bool Board::projectile_collide() {
    return false;
}

bool Board::rock_crush() {
    return false;
}

bool Board::cant_dig(sf::Vector2i to) {

    return !(blocks[to.y][to.x]->get_i_am_a() == "dirt");
}

void Board::check_tunnel(sf::Vector2i position)
{
    if ( blocks[position.y][position.x]->get_i_am_a() == "tunnel" ) {
        std::array<std::array<Sprite*, 3>, 3> adjacent_tunnels {get_adjacent_objects( position )};

        dynamic_cast<Tunnel*>(blocks[position.y][position.x])->get_tunnels( adjacent_tunnels );
    }
}

bool Board::collision_with_enemy() {
    return false;
}

bool Board::check_not_passable( sf::Vector2i passing_object_pos, sf::Vector2i object_pos )
{
    std::string passing_object_type {characters[passing_object_pos.y][passing_object_pos.x]->get_i_am_a()};

    return blocks[object_pos.y][object_pos.x]->check_not_passable( passing_object_type );
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
                        player = dynamic_cast<Player*>(characters[row][column]);
                        player->set_position(row, column);
                    }
                    else
                    {
                        enemies.push_back(dynamic_cast<Enemies*>(characters[row][column]));
                        auto enemy = enemies.rbegin();
                        (*enemy)->set_position(row, column);
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
    initialize_tunnels();
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

void Board::initialize_tunnels()
{
    for (int row = 0; row < blocks.size(); ++row)
    {
        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            check_tunnel({column, row});
        }
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
    sf::Time elapsed1 = time.getElapsedTime();
    std::cout << elapsed1.asSeconds() << std::endl;
    for (int row = 0; row < blocks.size(); ++row)
    {
        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            sf::Sprite block_sprite;
            sf::Sprite character_sprite;
            if (blocks[row][column] != nullptr ) {
                blocks[row][column]->draw( window_ptr, row, column, block_sprite );
            }
            if (characters[row][column] != nullptr)
            {
                characters[row][column]->draw( window_ptr, row, column, character_sprite);
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
    return new Background(depth);

}

void Board::player_action( std::string action )
{

    if ( !(action == "shoot" || action == "place" ) )
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

        check_tunnel(player_pos);
        check_tunnel({player->get_current_x(), player->get_current_y()});
        //player->animate();
    }
    else
    {

    }
}



void Board::moving_character(int x_mod, int y_mod, sf::Vector2i character_pos)
{
    Sprite* temp;
    sf::Vector2i to {character_pos.x + x_mod, character_pos.y + y_mod};

    if ( !check_collision(character_pos, to ) )
    {
        temp = characters[character_pos.y + y_mod][character_pos.x + x_mod];
        characters[character_pos.y + y_mod][character_pos.x + x_mod] = player;
        characters[character_pos.y][character_pos.x] = temp;

        player->set_position(character_pos.y + y_mod, character_pos.x + x_mod);
    }

}

Sprite *Board::create_player()
{
    return new Player();
}

Sprite *Board::create_demodog()
{
    return new Demodog();
}

std::array<std::array<Sprite*, 3>, 3> Board::get_adjacent_objects( sf::Vector2i mid_pos)
{
    std::array<std::array<Sprite *, 3>, 3> tunnel_objects{};
    int count{0};

    for (int y = 0; y < tunnel_objects.size(); ++y)
    {
        for (int x = 0; x < tunnel_objects[y].size(); ++x)
        {
            std::map<int, sf::Vector2i> modifiers{ {0, {-1, -1}}, {1, {0, -1}}, {2, {1, -1}},
                                                   {3, {-1, 0}},  {4, {0, 0}},  {5, {1, 0}},
                                                   {6, {-1, 1}},  {7, {0, 1}},  {8, {1, 1}} };

                int y_mod{modifiers[count].y};
                int x_mod{modifiers[count].x};

                if ( (mid_pos.y + y_mod < update_playstate->board_height) && (mid_pos.y + y_mod >= 2) &&
                     (mid_pos.x + x_mod < update_playstate->board_width ) && (mid_pos.x + x_mod >= 0) )
                {
                    tunnel_objects[y][x] = blocks[mid_pos.y+y_mod][mid_pos.x+x_mod];
                }
                else
                {
                       tunnel_objects[y][x] = nullptr;
                }

                ++count;
        }
    }
    return tunnel_objects;
}

void Board::dig( sf::Vector2i position )
{
    //dig animation here

    delete (blocks[position.y][position.x]);
    blocks[position.y][position.x] = create_tunnel(check_depth_level(position.y));
}
