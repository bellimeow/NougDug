//
// Created by isade842 on 12/8/17.
//

#ifndef NOUGAT_H
#define NOUGAT_H


#include "Sprite.h"

/** Class Nougat
 * Class for the projectile players shoot
 */

class Nougat : public Sprite
{
    private:
        std::string direction; /// What direction is it heading
        sf::Vector2i start_position; /// Initial position
        int rotation_value { 0 }; /// How much to rotate

    public:

        /// Constructor, takes direction
        explicit Nougat( const std::string &direction);

        /// Draw, does not use Sprite::draw
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite& rock_sprite) override;

        /// Animates, unused
        void animate() override;

        /// Gets projectile sprite sheet
        sf::Texture get_sprite_sheet() override ;

        /// What may and may not pass
        bool check_not_passable( std::string character) const override;

        /// Moves the projectile each tick
        void move() override;


        /// Getter and setter start_position
        const sf::Vector2i &get_start_position() const;
        void set_start_position( const sf::Vector2i &start_position );

        /// sets rotation value based on direction
        void set_rotation( std::string direction);

        /// getter direction
        const std::string &get_direction() const;
    };


#endif
