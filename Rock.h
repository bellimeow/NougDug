#ifndef ROCK_H
#define ROCK_H

#include "Block.h"

/** Class to handle blocks both as blocks and projectiles
 *
 */

class Rock : public Block
{

    private:

        sf::Vector2i start_position; /// Initial position when falling
        bool falling { false }; /// Whether the rock is falling or not

    public:

        /// Constructor takes depth
        explicit Rock ( int depth );

        /// Overridden draw function, handles falling and not falling differently
        void draw ( sf::RenderWindow* window, int row, int column, sf::Sprite& rock_sprite ) override;

        /// Currently unused
        void animate() override;

        /// Gets the rock texture
        sf::Texture get_sprite_sheet() override ;

        /// Check what may and may not pass
        bool check_not_passable( std::string character) const override;

        /// Getter falling
        bool is_falling() const;

        /// Setter falling
        void set_falling( bool falling );

        /// Overridden move used to move the block when falling
        void move() override;

        /// Getter and setter start_position
        const sf::Vector2i &get_start_position() const;
        void set_start_position( const sf::Vector2i &start_position );
};

#endif