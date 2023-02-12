#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <fstream>
#include "Sprite.h"

/** Class Character
 *  Handles the function all other characters hav in common
 */

class Character : public Sprite
{
    protected:

        const int lives{}; /// Character lives
        const int step{}; /// How large are the characters steps
        const int tick_len{}; /// How long is a tick for character
        bool is_alive { true }; /// Is the character alive
        std::string direction{}; /// Direction character is moving

    public:

        /// Constructor
        Character( int lives, int step, std::string object, int tick_len );

        /// Base for moving_object_collide
        virtual bool moving_object_collide(Sprite*) = 0;

        /// Getter & setter Direction
        const std::string &get_direction() const;
        void set_direction( const std::string &direction );

        /// Getter lives
        const int get_lives() const;

        /// Getter &  setter is_alive
        bool is_is_alive() const;

        void set_is_alive( bool is_alive );

};




#endif