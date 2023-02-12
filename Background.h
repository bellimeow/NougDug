#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Block.h"

/**
 * The background class is a subclass of Block. This class is used for drawing
 * only on the first position of the double vector of the blocks in Board.
 * The background is only one picture as large as the board width and three
 * rows down from the top of the window.
 * **/

class Background : public Block
{
    public:

        /// Constructor takes in depth since the Block constructor has depth.
        /// But depth is never used. All the other blocks uses depth.
        explicit Background(int depth);

        /// Drawing the background.
        void draw(sf::RenderWindow* window, int row, int column,
                  sf::Sprite& dirt_sprite) override;

        /// Get backgrounds specific sprite sheet.
        sf::Texture get_sprite_sheet() override;

        /// Used to check if background is passable by different objects.
        bool check_not_passable( std::string character) const override;

        /// Not yet implemented.
        void animate() override;
};

#endif