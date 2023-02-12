//
// Created by seblu114 on 12/12/17.
//

#include <iostream>
#include <random>
#include "Enemies.h"

Enemies::Enemies(int lives, std::string object, int hunt_timer)
    : Character(lives, 1, object, 50), hunt_timer{sf::seconds(hunt_timer)}
{
    set_dinner_time();
}

void Enemies::action(std::array<std::array<Sprite*, 3>, 3> possible_pos, sf::Vector2i player_position, sf::Clock &time)
{
    if(is_awake && is_alive && !is_eating)
    {
        if (can_hunt)
        {
            if (!ghost_hunting)
            {
                hunt(possible_pos, player_position);
            }
            else
            {
                ghost_hunt(player_position);
            }
        }
        else
        {
            patrol(possible_pos, time);
            check_dinner_time( time );
        }
    }
    else if ( !is_alive )
    {
        set_mark_for_delete (true);
    }
    else
    {
        direction_modifier = sf::Vector2i( 0, 0 );
    }
}

void Enemies::digestion()
{
    if ( is_eating )
    {
        --pumped;

        if (pumped <= 0 )
        {
            is_eating = false;
        }
    }
}

void Enemies::patrol(std::array<std::array<Sprite*, 3>, 3> possible_pos, sf::Clock &time)
{
    int time_passed{0};
    sf::Time prev_elapsed {time.getElapsedTime()};
    sf::Vector2i mid_pos {1,1};

    do
    {
        move_decision(); //My position + direction mod == lastpos

        time_passed = time.getElapsedTime().asMilliseconds() - prev_elapsed.asMilliseconds();
    } while(possible_pos[mid_pos.y + direction_modifier.y][mid_pos.x + direction_modifier.x] == nullptr ||
            current_position + direction_modifier == last_position ||
            (possible_pos[mid_pos.y + direction_modifier.y][mid_pos.x + direction_modifier.x] != nullptr/*onödig?*/ &&
             possible_pos[mid_pos.y + direction_modifier.y][mid_pos.x + direction_modifier.x]->get_i_am_a() != "tunnel" &&
             possible_pos[mid_pos.y + direction_modifier.y][mid_pos.x + direction_modifier.x]->get_i_am_a() != "background" &&
             time_passed < tick_len ));
    if (time_passed >= tick_len)
    {
        direction_modifier.x = 0;
        direction_modifier.y = 0;
    }
}

void Enemies::move_decision()
{
    /** Randomly sets one possible direction for the enemies
     *  It randomly selects an integer that corresponds to a position in the 2d array of possible positions **/

    std::random_device rd;
    std::uniform_int_distribution<int> range( 1, 4);
    std::map<int, sf::Vector2i> modifiers{ {1, {-1, 0}}, {2, {0, -1}},
                                           {3, {0, 1}},  {4, {1, 0}} };

    direction_modifier = modifiers[range(rd)];
}

void Enemies::ghost_hunt( sf::Vector2i player_position )
{
    if (!ghost_hunting )
    {
        ghost_hunting_position = player_position;
    }

    int delta_y     { abs (ghost_hunting_position.y - current_position.y ) };
    if (delta_y == 0)
    {
        delta_y = 1;
    }
    int direction_y { (ghost_hunting_position.y - current_position.y) / delta_y };
    int delta_x     { abs (ghost_hunting_position.x - current_position.x) };
    if (delta_x == 0)
    {
        delta_x = 1;
    }
    int direction_x { (ghost_hunting_position.x - current_position.x) / delta_x };

    direction_modifier.y = direction_y;
    direction_modifier.x = direction_x;

    if ( current_position.y + direction_modifier.y == ghost_hunting_position.y &&
         current_position.x + direction_modifier.x == ghost_hunting_position.x  )
    {

        ghost_hunting = false;
        ghost_hunting_complete = true;
    }
}

void Enemies::hunt( std::array<std::array<Sprite*, 3>, 3> adjacent_objects, sf::Vector2i player_position )
{
    std::vector<sf::Vector2i> array_positions{{1, 0},
                                              {0, 1},
                                              {2, 1},
                                              {1, 2}};
    int path_count {};

    for (int i = 0; i < array_positions.size(); ++i)
    {
        if (adjacent_objects[array_positions[i].y][array_positions[i].x] != nullptr &&
            (adjacent_objects[array_positions[i].y][array_positions[i].x]->get_i_am_a() == "background" ||
             adjacent_objects[array_positions[i].y][array_positions[i].x]->get_i_am_a() == "tunnel"))
        {

            ++path_count;
        }
    }

    std::vector< sf::Vector2i> moving_modifiers{ {1, 0}, {0, -1},
                                                 {0, 1}, {-1, 0},
                                                 {1, 2}, {0, 1},
                                                 {2, 1}, {1, 0} };

    if ( path_count >= 2 )
    {

        int delta_y{abs(player_position.y - current_position.y)};
        if (delta_y == 0)
        {

            delta_y = 1;
        }
        int direction_y{(player_position.y - current_position.y) / delta_y};
        int delta_x{abs(player_position.x - current_position.x)};
        if (delta_x == 0)
        {
            delta_x = 1;
        }
        int direction_x{(player_position.x - current_position.x) / delta_x};

        if (delta_y > delta_x && direction_y != 0 )
        {
            if (adjacent_objects[direction_y + 1][1]->get_i_am_a() == "dirt" )
            {
                for ( int moving_modifier = 0; moving_modifier < moving_modifiers.size(); moving_modifier += 2 )
                {
                    if ( adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x] != nullptr &&
                            adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_i_am_a() != "dirt" &&
                            adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_i_am_a() != "rock" &&
                         adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_current_pos()  != last_position )
                    {
                        direction_modifier.y = moving_modifiers[moving_modifier+1].y;
                        direction_modifier.x = moving_modifiers[moving_modifier+1].x;
                    }
                }

            }
            else
            {
                direction_modifier.y = direction_y;
                direction_modifier.x = 0;
            }
            past_direction_modifier = direction_modifier;

        }
        else
        {
            if (adjacent_objects[1][direction_x + 1]->get_i_am_a() == "dirt" )
            {
                for ( int moving_modifier = 0; moving_modifier < moving_modifiers.size(); moving_modifier += 2 )
                {
                    if ( adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x] != nullptr &&
                         adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_i_am_a() != "dirt" &&
                         adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_i_am_a() != "rock" &&
                         adjacent_objects[moving_modifiers[moving_modifier].y][moving_modifiers[moving_modifier].x]->get_current_pos()  != last_position )
                    {
                        direction_modifier.y = moving_modifiers[moving_modifier+1].y;
                        direction_modifier.x = moving_modifiers[moving_modifier+1].x;
                    }
                }

            }
            else
            {
                direction_modifier.y = 0;
                direction_modifier.x = direction_x;
            }
            past_direction_modifier = direction_modifier;
        }
        if (current_position + direction_modifier == last_position)
        {
            ++stuck_count;
        }
    }

    else
    {
        if ( adjacent_objects[direction_modifier.y + 1][direction_modifier.x + 1]->get_i_am_a() == "dirt" )
        {

            ghost_hunting = true;
            ghost_hunting_position = player_position;
        }
    }

    if (  stuck_count > 2 && !ghost_hunting_complete )
    {
        ghost_hunting = true;
        ghost_hunting_position = player_position;
    }
}

void Enemies::in_hunt_range( sf::Vector2i player_position )
{
    if (!can_hunt)
    {
        int hunting_range{3};

        int left{current_position.x - hunting_range};
        int top{current_position.y - hunting_range};

        int right{current_position.x + hunting_range};
        int bottom{current_position.y + hunting_range};

        sf::Vector2i left_top_coordinate{left, top};
        sf::Vector2i bottom_right_coordinate{right, bottom};

        can_hunt = (player_position.x >= left_top_coordinate.x && player_position.x <= bottom_right_coordinate.x &&
                    player_position.y >= left_top_coordinate.y && player_position.y <= bottom_right_coordinate.y);
    }
}

void Enemies::set_is_awake( bool is_awake )
{
    Enemies::is_awake = is_awake;
}

void Enemies::set_dinner_time()
{
    std::random_device rd;
    std::uniform_int_distribution<int> range( 5, 10);

    hunt_timer = sf::seconds( range(rd) );
}

bool Enemies::moving_object_collide(Sprite* object)
{
    return (object->get_current_pos() == current_position);
}

void Enemies::check_dinner_time(sf::Clock &time)
{
    if ( hunt_timer.asSeconds() >= time.getElapsedTime().asSeconds() );
    {
        can_hunt = true;
    }

}

const sf::Vector2i &Enemies::get_direction_modifier() const
{
    return direction_modifier;
}

void Enemies::set_last_position( const sf::Vector2i &last_position )
{
    Enemies::last_position = last_position;
}

int Enemies::get_pumped() const
{
    return pumped;
}

void Enemies::set_pumped( int pumped )
{
    Enemies::pumped = pumped;
}

bool Enemies::is_ghost_hunting() const {
    return ghost_hunting;
}

bool Enemies::get_is_eating() const
{
    return is_eating;
}

void Enemies::set_is_eating( bool is_eating )
{
    Enemies::is_eating = is_eating;
}
