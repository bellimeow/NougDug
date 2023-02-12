#ifndef ENEMIES_H
#define ENEMIES_H

#include "Character.h"

/** Enemies handles enemies and their behaviours
 * Whether to patrol, hunt och pas through the earth
 *
 */

class Enemies : public Character
{
    protected:

        sf::Time hunt_timer; /// Time before enemy starts hunting player
        bool can_hunt { false };
        bool is_eating { false }; /// Is the enemy eating nougat, i.e. can be passed
        bool is_awake { false }; /// Is the enemy awake, i.e. has the player made their first action
        int pumped { 0 }; /// How bloated is the enemy
        sf::Vector2i direction_modifier { 0, 0 }; /// modifier to determine direction to move
        sf::Vector2i past_direction_modifier { 0,0 }; /// last direction modifier
        sf::Vector2i last_position {}; /// previous position
        sf::Texture demodog_ghost_sheet{}; /// Extra sprite sheet for ghost hunt
        int stuck_count{}; /// How many times enemys been stuck
        bool ghost_hunting_complete{false}; /// Has the enemy ghost hunted once

        bool ghost_hunting{false}; /// Is the enemy ghost hunting (walking through walls)
        sf::Vector2i ghost_hunting_position {}; /// Goal to reach for ghost hunt

        /// Randoms a direction to move, "deciding" for the enemy
        virtual void move_decision();

        /// Handles ghost hunting
        void ghost_hunt( sf::Vector2i player_position );

        /// Checks if total time passed is greater than hunt timmer and then allows hunting
        virtual void check_dinner_time(sf::Clock &time);

        /// Randoms the hunt timer from an interval
        virtual void set_dinner_time();

        /// Handles the enemy patrolling, uses move decision, takes 2d array of near by object
        virtual void patrol(std::array<std::array<Sprite*, 3>, 3> possible_pos, sf::Clock &time);

        /// Handles regular hunting, takes 2d array of near by object
        void hunt(std::array<std::array<Sprite *, 3>, 3> possible_pos, sf::Vector2i player_position);

    public:

        /// Constructor
        Enemies(int lives, std::string object, int hunt_timer);

        /// Decides what action the enemy should takem uses array of near objects, players position and a clock
        virtual void action (std::array<std::array<Sprite*, 3>, 3> possible_pos,
                             sf::Vector2i player_position, sf::Clock &time);

        /// Setter last position
        void set_last_position( const sf::Vector2i &last_position );

        /// Checks if the player is close enought to trigger a hunt
        void in_hunt_range( sf::Vector2i player_position );

        /// Checks collision wiht moving objects, i.e. projectiles, player, etc
        bool moving_object_collide(Sprite* object) override;

        /// Setter is_awake
        void set_is_awake( bool is_awake );

        /// Getter direction modifier
        const sf::Vector2i &get_direction_modifier() const;

        /// Getter & setter pumped
        int get_pumped() const;
        void set_pumped( int pumped );

        /// getter ghost hunting
        bool is_ghost_hunting() const;

        /// getter & setter is_eating
        bool get_is_eating() const;
        void set_is_eating( bool is_eating );

        /// reduces pumped and resets is eating if pumped <= 0
        void digestion();
};


#endif