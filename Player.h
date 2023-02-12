#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <fstream>
#include "Character.h"

/** Class Player
 * handles the player like other sprites
 *
 */

class Player : public Character
{
    private:

        bool can_shoot{true}; /// Can the player shoot
        bool invulnerable{false}; /// Can the player be damaged


    public:

        /// Constructor
        Player();

        /// Animate, unused, except for tests
        void animate() override;

        /// Draw the player
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite& player_sprite) override;

        /// Getter step, Currently unused
        const int get_step() const;;

        /// Getter can_shoot, unused
        bool get_can_shoot() const;

        /// Getter and setter invulnerable
        bool get_invulnerable() const;
        void set_invulnerable( bool invulnerable );

        /// Gets and returns players spritesheet
        sf::Texture get_sprite_sheet() override;

        /// What may and may not pass
        bool check_not_passable(std::string) const override;

        /// Check for basic collision with objects not i the board 2d vector
        bool moving_object_collide(Sprite* object) override;


};

#endif