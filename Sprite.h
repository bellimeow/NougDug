#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include "SpritesType.h"
#include "Game.h"

class Sprite
{
        /** Sprite - Base class for all object that draw themselves
         *  Sprite handles all that has to do with, drawing, size
         *  position and textures
         * */

    protected:

        sf::Texture texture; /// Texture object will use to draw itself
        sf::Vector2i current_position; /// Objects current position in the 2d vector representing the board
        sf::Vector2i real_position; /// Objects "real" position, i.e. actual pixel position on screen
        std::string i_am_a { "sprite" }; /// Answers "What is this object?"
        int height { 16 }; /// Objects height, defaults to 16, i.e. base size of a tile in game
        int width { 16 }; /// Objects width, defaults to 16, i.e. base size of a tile in game
        int scale { Game::DISPLAY_SIZE_MULTIPLIER }; /// Objects scale, based on the display multiplier set in Game
        bool mark_for_delete{ false }; /// Should it be deleted

        static std::map< std::string, sf::Texture*> sprite_sheets;  /// Map that holds all object textures

    public:
        static const std::string sprite_sheet_path; /// Holds path to textures

        /// Default constructor
        Sprite();

        /// Constructor, takes string and sets i_am_a
        Sprite(std::string);

        /// Base draw function, used by most draw functions, scales sprites, moves them to their real
        /// position and draws them in the window
        virtual void draw ( sf::RenderWindow* window_ptr, int row, int column, sf::Sprite& sprite );

        /// Base function to get sprite sheets, for sub classes
        virtual sf::Texture get_sprite_sheet();

        /// Static sprite sheet function, part of unfinished part to change handlinff of textures
        static sf::Texture* get_sprite_sheet ( std::string type );

        /// Static function, loads all object textures
        static void load_sprite_sheets();

        /// Takes a SpriteType, returns position of texture to use
        static sf::IntRect extract_texture_position ( SpriteType sprite_type );

        /// Base animate, currently unused
        virtual void animate();

        /// Base move, to be used with animate, currently unused
        virtual void move();

        /// Pure virtual for all other classes
        virtual bool check_not_passable ( std::string ) const = 0;

        /// Getter i_am_a
        const std::string &get_i_am_a() const;

        /// Sets current_position using to values
        void set_position ( int y, int x );

        /// Getters for current_position.x and current_postion.y respectively
        int get_current_x() const;
        int get_current_y() const;

        /// Getter for current_position
        sf::Vector2i get_current_pos() const;

        /// Getter for real_position
        sf::Vector2i get_real_pos() const;

        /// Setters for real_position
        void set_real_position();
        void set_real_position( int y, int x );

        /// Getter and setter for mark_for_delete
        bool get_mark_for_delete() const;
        void set_mark_for_delete( bool mark_for_delete );
};

#endif