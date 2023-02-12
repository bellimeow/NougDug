//
// Created by seblu114 on 12/6/17.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cmath>
#include "Board.h"
#include "Dirt.h"
#include "Rock.h"
#include "Tunnel.h"
#include "Demodog.h"
#include "Background.h"
#include "Nougat.h"
#include "Score.h"

typedef Sprite* (*BlockFunction)(int);
typedef std::unordered_map<char, BlockFunction> BlockFunctionMap;

typedef Sprite* (*CharacterFunction)(void);
typedef std::unordered_map<char, CharacterFunction> CharacterFunctionMap;

std::array<std::array<Sprite*, 3>, 3> Board::get_adjacent_objects( sf::Vector2i mid_pos)
{
    std::array<std::array<Sprite *, 3>, 3> objects{};
    int count{0};

    for (auto &object : objects) {
        for (auto &x : object) {
            std::map<int, sf::Vector2i> modifiers{ {0, {-1, -1}}, {1, {0, -1}}, {2, {1, -1}},
                                                   {3, {-1, 0}},  {4, {0, 0}},  {5, {1, 0}},
                                                   {6, {-1, 1}},  {7, {0, 1}},  {8, {1, 1}} };

            int y_mod{modifiers[count].y};
            int x_mod{modifiers[count].x};

            if ( (mid_pos.y + y_mod < play_state->board_height) && (mid_pos.y + y_mod >= 2) &&
                 (mid_pos.x + x_mod < play_state->board_width ) && (mid_pos.x + x_mod >= 0) )
            {
                x = blocks[mid_pos.y+y_mod][mid_pos.x+x_mod];
            }
            else
            {
                x = nullptr;
            }

            ++count;
        }
    }
    return objects;
}

bool Board::check_collision(Character* from, sf::Vector2i to)
{
    if (from->get_i_am_a() == "demodog" && dynamic_cast<Enemies*>(from)->is_ghost_hunting())
    {
        return false;
    }

    if (check_not_passable(from, to))
    {
        if (cant_dig(to, from))
        {
            return true;
        }
        dig(to);
        Score::calculate_score(dynamic_cast<Block *>(blocks[to.y][to.x])->get_depth(), ScoreType::DIG);
    }
    return false;
}

bool Board::rock_proximity( sf::Vector2i position )
{
    return ( blocks[position.y-1][position.x]->get_i_am_a() == "rock" );
}

bool Board::projectile_collide( Sprite* projectile )
{
    sf::Vector2i real_pos { projectile->get_real_pos() };
    int possible_x { static_cast<int>(std::round( real_pos.x / (16*Game::DISPLAY_SIZE_MULTIPLIER ))) };
    int possible_y { static_cast<int>(std::round( real_pos.y / (16*Game::DISPLAY_SIZE_MULTIPLIER) ))};

    std::map<std::string, sf::Vector2i> proj_pos{ {"up",    {0, -1}},
                                                  {"right", {1, 0 }},
                                                  {"down",  {0, 1 }},
                                                  {"left",  {-1, 0}} };


    sf::Vector2i possible_position{possible_x, possible_y};
    sf::Vector2i possible_valid_position{possible_x, possible_y};

    if( projectile->get_i_am_a() == "nougat" && inbounds( possible_valid_position + proj_pos[dynamic_cast<Nougat*>(projectile)->get_direction()]) )
    {
        possible_valid_position += proj_pos[dynamic_cast<Nougat*>(projectile)->get_direction()];
    }

    if ( inbounds( possible_position ) )
    {
        if ( check_not_passable( projectile, possible_valid_position ) )
        {
            sf::Vector2i possible_real_pos { blocks[possible_position.y][possible_position.x]->get_real_pos() };

            return (intersect(projectile->get_real_pos(), possible_real_pos));
        }

        if (projectile_collision_with_enemy( projectile ) )
        {
            return true;
        }

        if (projectile->get_i_am_a() == "nougat" )
        {
            auto nougat = dynamic_cast<Nougat*>( projectile );

            return (possible_position.x >= nougat->get_start_position().x + 3 ||
                    possible_position.y >= nougat->get_start_position().y + 3);
        }

        return false;

    }
    else
    {
        return true;
    }
}

bool Board::rock_fall( sf::Vector2i position ) {
    if ( blocks[position.y][position.x]->get_i_am_a() == "tunnel" )
    {
        delete (blocks[position.y - 1][position.x]);
        blocks[position.y - 1][position.x] = create_dirt( check_depth_level( position.y - 1 ));

        projectiles.push_back( new Rock( check_depth_level( position.y ) ) ) ;

        auto rock = dynamic_cast<Rock*>( *projectiles.rbegin() );
        rock->set_position(position.y, position.x);
        rock->set_start_position( rock->get_current_pos() );
        rock->set_real_position();
        rock->set_falling( true );
    }
}

bool Board::cant_dig(sf::Vector2i to, Character* from)
{

    return !(( blocks[ to.y ][ to.x ]->get_i_am_a () == "dirt" ) &&
             ( from->get_i_am_a () == "player" ));
}

bool Board::projectile_collision_with_enemy(Sprite*& projectile)
{
    auto it = std::find_if( std::begin(enemies), std::end(enemies), [this, &projectile](auto enemy)
    {
        return ( is_intersect( enemy, projectile ) );
    } );

    if ( it != std::end(enemies) && projectile->get_i_am_a() == "nougat" )
    {
        if ( (*it)->get_lives() > (*it)->get_pumped() )
        {
            int pumped { (*it)->get_pumped() + 1 };

            (*it)->set_pumped(pumped);
            (*it)->set_is_eating(true);
        }
        else
        {
            Score::calculate_score(dynamic_cast<Block*>(blocks[(*it)->get_current_y()][(*it)->get_current_x()])->get_depth(), ScoreType::KILLED_DEMODOG);
            (*it)->set_is_alive(false);
        }

        return true;
    }
    else if ( it != std::end(enemies) && projectile->get_i_am_a() == "rock" )
    {
        Score::calculate_score(dynamic_cast<Block*>(blocks[(*it)->get_current_y()][(*it)->get_current_x()])->get_depth(), ScoreType::ROCK_KILLED_DOG);
        (*it)->set_is_alive(false);

        return true;
    }
}

bool Board::check_not_passable( Sprite* passing_object, sf::Vector2i object_pos )
{
    const std::string &passing_object_type {passing_object->get_i_am_a()};

    return blocks[object_pos.y][object_pos.x]->check_not_passable( passing_object_type );
}

void Board::insert_objects( std::ifstream* ifs)

{
    BlockFunctionMap block_map{create_block_function_map()};
    CharacterFunctionMap character_map{create_character_function_map()};

    char obj_char;

    int depth_level {1};

    for (int row = 0; row < blocks.size(); ++row)
    {
        depth_level = check_depth_level(row);

        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            while( ifs->get(obj_char) )
            {
                if (block_map.count(obj_char) > 0)
                {
                    BlockFunction function = block_map[obj_char];
                    blocks[row][column] = (*function)(depth_level);
                    blocks[row][column]->set_position(row, column);
                    blocks[row][column]->set_real_position();

                    if (obj_char == 'R')
                    {
                        ++rock_count;
                    }

                    break;
                }
                else if (character_map.count(obj_char) > 0)
                {
                    CharacterFunction function = character_map[obj_char];
                    blocks[row][column] = create_tunnel(depth_level);

                    if (obj_char == '@')
                    {
                        player = dynamic_cast<Player*>((*function)());
                        player->set_position(row, column);
                        player->set_real_position();
                        play_state->current_player_lives = player->get_lives();
                    }
                    else
                    {
                        enemies.push_back(dynamic_cast<Enemies*>((*function)()) );
                        auto enemy = enemies.rbegin();
                        (*enemy)->set_position(row, column);
                        (*enemy)->set_real_position();
                        (*enemy)->set_last_position((*enemy)->get_current_pos());
                        ++enemy_count;
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
    for (auto &row : object_vector) {
        row.resize(width);
        std::fill( row.begin(), row.end(), null);
    }
}

void Board::moving_character(sf::Vector2i move_pos, Character* character)
{
    if ( !check_collision(character, move_pos ) )
    {
        character->set_position(move_pos.y, move_pos.x);
        character->set_real_position();
    }

}

void Board::dig( sf::Vector2i position )
{

    delete (blocks[position.y][position.x]);
    blocks[position.y][position.x] = create_tunnel(check_depth_level(position.y));
    blocks[position.y][position.x]->set_position(position.y, position.x);
    blocks[position.y][position.x]->set_real_position();
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
    return new Background(depth);
}

Sprite *Board::create_player()
{
    return new Player();
}

Sprite *Board::create_demodog()
{
    return new Demodog();
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

bool Board::is_intersect( Sprite* object_a, Sprite* object_b )
{
    return ( intersect( object_a->get_real_pos(), object_b->get_real_pos() ) );
}

void Board::clean_up()
{

    for (auto it = std::begin(projectiles); it != std::end(projectiles); )
    {
        Sprite*& projectile {*it};

        if ( projectile->get_mark_for_delete() )
        {
            delete(projectile);
            it = projectiles.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = std::begin(enemies); it != std::end(enemies); )
    {
        Enemies*& enemy {*it};

        if ( enemy->get_mark_for_delete() )
        {
            delete(enemy);
            it = enemies.erase(it);
            --enemy_count;
        }
        else
        {
            ++it;
        }
    }

}

Board::Board(std::ifstream* game_board, const int width, const int height, PlayState* ps, sf::RenderWindow* window)
        : BACKGROUND_DEPTH{3}, play_state{ps}, window_ptr{window}
{
    set_board_size(blocks, width, height);

    set_depth_levels();

    Sprite::load_sprite_sheets();

    insert_objects(game_board);
}

Board::~Board ()
{
    delete (player);
    delete_enemies();
    delete_projectiles();
    delete_blocks();
    delete_sprite_sheets();
}

BlockFunctionMap Board::create_block_function_map()
{
    BlockFunctionMap func;
    func.emplace('D', &create_dirt);
    func.emplace('T', &create_tunnel);
    func.emplace('R', &create_rock);
    func.emplace('B', &create_background);
    //func.emplace('&', &create_root);
    //func.emplace('X', &create_extra_points);

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

void Board::player_action( std::string action )
{
    if ( first_action )
    {
        std::for_each( std::begin( enemies ), std::end( enemies ),
                       []( Enemies *enemy ) { enemy->set_is_awake( true ); } );

        first_action = false;
    }


    if ( !(action == "shoot" || action == "place" ) )
    {
        sf::Vector2i player_pos {player->get_current_x(), player->get_current_y()};

        std::map<std::string, sf::Vector2i> direction_values{ {"up",    {0, -1}},
                                                              {"right", {1, 0 }},
                                                              {"down",  {0, 1 }},
                                                              {"left",  {-1, 0}} };

        if ( ( action == "right" && player_pos.x < play_state->board_width - 1 ) ||
             ( action == "left" && player_pos.x > 0 ) ||
             ( action == "up" && player_pos.y > BACKGROUND_DEPTH - 1 ) ||
             ( action == "down" && player_pos.y < play_state->board_height - 1 ) )
        {
            sf::Vector2i move_pos {player_pos.x + direction_values[action].x, player_pos.y + direction_values[action].y};

            moving_character(move_pos, player);

            player->set_direction(action);

            if ( rock_proximity( move_pos ) )
            {
                rock_fall( move_pos );
            }

            check_tunnel(player_pos);
            check_tunnel({player->get_current_x(), player->get_current_y()});

        };
    }
    else if ( action == "shoot")
    {
        player_shoot();
    }
}

void Board::draw()
{
    for (int row = 0; row < blocks.size(); ++row)
    {
        for (int column = 0; column < blocks[row].size() ; ++column)
        {
            sf::Sprite block_sprite;
            if (blocks[row][column] != nullptr ) {
                blocks[row][column]->draw( window_ptr, row, column, block_sprite );
            }
        }
    }
    sf::Sprite player_sprite;
    player->draw(window_ptr, player->get_current_y(), player->get_current_x(), player_sprite);

    std::for_each( std::begin( enemies ), std::end( enemies ), [this]( Enemies* enemy )
    {
        sf::Sprite enemy_sprite;
        enemy->draw( window_ptr, enemy->get_current_y(), enemy->get_current_x(), enemy_sprite );
    } );

    std::for_each( std::begin( projectiles ), std::end( projectiles ), [this]( Sprite* projectile )
    {
        sf::Sprite projectile_sprite;
        sf::Vector2i real_pos {projectile->get_real_pos()};

        projectile->draw( window_ptr, real_pos.y, real_pos.x, projectile_sprite );
    } );

    play_state->create_high_score();
    play_state->display_player_lives();
}

void Board::set_depth_levels()
{
    unsigned int height {play_state->board_height};

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

void Board::check_tunnel( sf::Vector2i position )
{
    if ( blocks[position.y][position.x]->get_i_am_a() == "tunnel" ) {
        std::array<std::array<Sprite*, 3>, 3> adjacent_tunnels {get_adjacent_objects( position )};

        dynamic_cast<Tunnel*>(blocks[position.y][position.x])->get_tunnels( adjacent_tunnels );
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

int Board::get_enemy_count() const
{
    return enemy_count;
}

void Board::update()
{

    /// Enemy Update ///
    if ( passed_time( enemy_time ) > 300 )
    {
        update_enemies();

        enemy_time = time.getElapsedTime();
    }


    if ( passed_time( reset_status_time ) > 1000)
    {
        player->set_invulnerable(false);

        std::for_each( std::begin(enemies), std::end(enemies), []( auto enemy ){ enemy->digestion(); });

        reset_status_time = time.getElapsedTime();
    }


    enemy_player_collision();

    update_projectiles();

    clean_up();
}

void Board::player_shoot()
{
    sf::Sprite nougat_sprite;
    projectiles.push_back( new Nougat( player->get_direction() ) );
    auto * nougat = dynamic_cast<Nougat*>( *projectiles.rbegin() );
    nougat->set_position(player->get_current_y(), player->get_current_x() );
    nougat->set_start_position( player->get_current_pos() );
    nougat->set_real_position();
}

bool Board::intersect( sf::Vector2i const &object_a, sf::Vector2i const &object_b ) const
{
    int fill{ 16 * Game::DISPLAY_SIZE_MULTIPLIER };

    return ((( object_a.x < object_b.x + fill ) && ( object_a.x + fill > object_b.x )) &&
            (( object_a.y < object_b.y + fill ) && ( object_a.y + fill > object_b.y )));
}

bool Board::inbounds(sf::Vector2i position)
{
    return ((position.y < play_state->board_height) && (position.y >= 0) &&
            (position.x < play_state->board_width ) && (position.x >= 0));
}

void Board::update_enemies()
{
    for (auto it { enemies.begin() }; it < enemies.end(); ++it)
    {
        Enemies* enemy {*it};
        std::array<std::array<Sprite*, 3>, 3> near_objects {get_adjacent_objects( enemy->get_current_pos() )};


        enemy->in_hunt_range( player->get_current_pos() );

        enemy->action(near_objects, player->get_current_pos(), time);

        sf::Vector2i enemy_pos {enemy->get_current_pos()};
        sf::Vector2i direction_modifier {enemy->get_direction_modifier()};
        sf::Vector2i move_pos {enemy_pos.x + direction_modifier.x, enemy_pos.y + direction_modifier.y};

        moving_character(move_pos, enemy);
        enemy->set_last_position(enemy_pos);
        enemy->set_position(move_pos.y, move_pos.x);

        if ( enemy->get_lives() <= enemy->get_pumped() )
        {
            enemy->set_mark_for_delete(true);
        }
    }
}

void Board::update_projectiles()
{
    std::for_each( std::begin( projectiles ), std::end( projectiles ), [this]( auto it )
    {
        if ( it->get_i_am_a() == "rock" && dynamic_cast<Rock*>(it)->get_start_position() == it->get_current_pos() )
        {
            it->move();
        }
        else if ( projectile_collide(it) )
        {
            it->set_mark_for_delete( true );
        }
        else
        {
            it->move();
        }

    });
}

void Board::enemy_player_collision()
{
    for (auto enemy = std::begin(enemies); enemy < std::end(enemies); ++enemy) {
        if ( intersect( (*enemy)->get_real_pos(), player->get_real_pos() ) &&
             !player->get_invulnerable() && !(*enemy)->get_is_eating())
        {
            std::cout << play_state->current_player_lives << "\n";
            --play_state->current_player_lives;
            player->set_invulnerable(true);
            sf::Time reset_status_time{sf::Time::Zero};
        }
    }
}


int Board::passed_time( sf::Time previous )
{
    return time.getElapsedTime().asMilliseconds() - previous.asMilliseconds();
}

void Board::delete_enemies ()
{
    std::for_each (enemies.begin (), enemies.end (), []( auto enemy ){ delete (enemy);});
}

void Board::delete_projectiles ()
{
    std::for_each (projectiles.begin (), projectiles.end (), []( auto projectile ){ delete (projectile);});
}

void Board::delete_blocks ()
{
    for (int row = 0; row < blocks.size(); ++row)
    {
        for ( int column = 0; column < blocks[ row ].size (); ++column )
        {
            delete(blocks[row][column]);
        }
    }
}

void Board::delete_sprite_sheets ()
{
    std::for_each (enemies.begin (), enemies.end (), []( auto enemy ){ delete (enemy);});
}
