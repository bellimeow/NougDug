#ifndef DEMODOG_H
#define DEMODOG_H

#include "Enemies.h"

/** Class Demodog
 * Handles the first enemy, demodogs
 *
 */

class Demodog : public Enemies
{
    private:




    public:

        /// Constructor
        Demodog();

        /// unused
        void animate() override;

        /// Draw, handles normal, ghost hunting, dead, and pumped diffrently
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite& enemy_sprite) override;

        /// Gets Demodogs sprite_sheet
        sf::Texture get_sprite_sheet() override ;

        /// Whar may and may not pass through
        bool check_not_passable( std::string ) const override;

};


#endif