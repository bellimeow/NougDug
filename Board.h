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
#include "Block.h"

class PlayState;

/** Class Board
 *  Simulates and handles the game board.
 *  Tracks all objects and handles collsion
 */

class Board
{
    private:
        int const BACKGROUND_DEPTH; /// How much of the board the is background

        int enemy_count { 0 }; /// How many enemies are on the board
        int rock_count { 0 }; /// How many rocks on the board
        std::vector<std::vector<Sprite*>> blocks; /// Holds all blocks on the boards, i.e. all static items and rock
        sf::RenderWindow* window_ptr; /// The Renderwindow
        Player* player; /// Tracks the player
        std::vector<Enemies*> enemies; /// Treacks enemies
        std::vector<Sprite*> projectiles; /// Tracks projectiles
        PlayState* play_state{}; /// Pointer to playstate that made it
        sf::Clock time{}; /// Main time
        sf::Time enemy_time{sf::Time::Zero}; /// Time to handle enemy events
        sf::Time reset_status_time{sf::Time::Zero}; /// Time to reset statuses
        sf::Time anim_time{sf::Time::Zero}; /// Time for animation
        std::map<int, int> depth_levels{   {1, 0},  /// Map to store limits for the depth levels
                                           {2, 0},
                                           {3, 0},
                                           {4, 0}   };
        bool first_action{true}; /// TBool to check player forst action

        ///Gets array of all adjacent objects, ising position from blocks
        std::array<std::array<Sprite*, 3>, 3> get_adjacent_objects(sf::Vector2i mid_pos);

        /// Checks basic collision
        bool check_collision(Character* from, sf::Vector2i to);

        /// Check if character is about to pass a rock
        bool rock_proximity( sf::Vector2i position );

        /// Collision with projectiles
        bool projectile_collide(Sprite* projectile);

        /// Make rocks fall, by converting to projectiles leaving dirt in it's place
        bool rock_fall( sf::Vector2i position );

        /// Checks if object can't be dug
        bool cant_dig(sf::Vector2i to, Character* from);

        /// Collision with projectiles for enemies
        bool projectile_collision_with_enemy(Sprite*& projectile);

        /// Helper to to check not passable on object being passed
        bool check_not_passable( Sprite* passing_object, sf::Vector2i object_pos );

        /// Converts characters in filestream to objects and places them in blocks or respective vector
        void insert_objects(std::ifstream* ifs);

        /// Sets size of the vectors to the wanted board size
        void set_board_size(std::vector<std::vector<Sprite*>>& object_vector, const unsigned int width, const unsigned int height);

        /// Handles characters moving, collison checks here
        void moving_character(sf::Vector2i move_pos, Character* character);

        /// Digs a block, i.e. replaces one object (dirt) with another (tunnel)
        void dig (sf::Vector2i position);

        /// Small functions to create objects used in map below
        static Sprite* create_dirt(int);
        static Sprite* create_tunnel(int);
        static Sprite* create_rock(int);
        //static Sprite* create_root(int);
        //static Sprite* create_extra_points(int);
        static Sprite* create_background(int);
        static Sprite* create_player();
        static Sprite* create_demodog();

        /// Initializes tunnels , making sure they use the right texture and rotation
        void initialize_tunnels();

        /// Helps hhecks whether two objects are intersecting
        bool is_intersect( Sprite* object_a, Sprite* object_b );

        /// Cleans up (removes) items no longer being used
        void clean_up();

    public:
        /// Constructor
        Board(std::ifstream* game_board, int width, int height, PlayState* ps, sf::RenderWindow* window);

        // Destructor
        ~Board();

        /// Creates unordered maps holding function pointers
        std::unordered_map<char, Sprite* (*)(int)> create_block_function_map();
        std::unordered_map<char, Sprite* (*)(void)> create_character_function_map();

        /// Handles player input sent from playstate
        void player_action(std::string);

        /// Calls all individual object draw functions
        void draw();

        /// Checks the board size and sets where each depth level begins
        void set_depth_levels();

        /// Checks what texture and rotation to use for a individual tunnel at position
        void check_tunnel (sf::Vector2i position);

        /// Check which depth level row corresponds to
        int check_depth_level (int const row);

        /// getter enemy count
        int get_enemy_count() const;

        /// Update, updates enemies, projectiles and statuses based on time, Cleans up after
        void update();

        /// Handles the player shooting
        void player_shoot();

        /// Checks whter object a and object_b intersects
        bool intersect( const sf::Vector2i &object_a, const sf::Vector2i &object_b ) const;

        /// Checks if position if in the allowed game board
        bool inbounds(sf::Vector2i position);

        /// Updates the enemies, checking action, moving themetc.
        void update_enemies();

        /// updates projectiles, moving them
        void update_projectiles();

        /// Checks player and enemies colliding
        void enemy_player_collision();

        /// checks timme passed since previous
        int passed_time( sf::Time previous );

        /// Destructor helpers
        void delete_enemies ();
        void delete_projectiles ();
        void delete_blocks ();
        void delete_sprite_sheets ();
};

#endif