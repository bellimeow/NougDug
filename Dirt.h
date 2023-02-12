#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

/** Class Dirt
 *  handles the diggable dirt blocks in the game
 */

class Dirt : public Block
{

    private:


    public:

        /// Constructor
        Dirt(int depth);

        /// Draw, draws different depending on depth
        void draw(sf::RenderWindow* window, int row, int column, sf::Sprite& dirt_sprite) override;

        /// Unused
        void animate() override;

        /// Gets dirts sprite sheet
        sf::Texture get_sprite_sheet() override;

        /// What may and may not pass through
        bool check_not_passable( std::string character) const override;



};

#endif