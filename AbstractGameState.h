#ifndef ABSTRACTGAMESTATE_H
#define ABSTRACTGAMESTATE_H

#include <string>
#include "Game.h"

/**
 * AbstractGameState a base class that is used mostly for pure virtual
 * functions that MenuState, PlayState and EndState use.
 *
 * There are functions to create the high score so that the subclasses can
 * display high score. There are also functions for updating the state,
 * initializing the state and drawing the states.
 *
 * AbstractGameState load all the sprite sheets that the different game states
 * use. And it also uses a static function in the Sprite class to extract a
 * certain sheet position from the high score number sheet and stores it in a
 * map. There is also a window pointer for all the states so they are able to
 * draw in the same window.
 * **/

class Game;

class AbstractGameState
{
    protected:

        /// Variable that is used for creating the high score.
        static int high_score;

        /// Used to change state.
        Game* game { nullptr };

        /// Used for drawing purposes.
        sf::RenderWindow* window_ptr { nullptr };

        /// The directory for the sprite sheets used in all the states.
        static const std::string sprite_sheet_path;

        /// Stores all the loaded sprite sheets.
        static std::map< std::string, sf::Texture*> sprite_sheets;

        /// Part of number sprite sheet, used for the high score.
        static std::map<char, sf::IntRect> number_sprite_sheets;

    public:

        /// Check the current state.
        virtual void check_state() = 0;

        /// Changes the state to a specific state.
        virtual void change_state() = 0;

        /// Starting the state.
        virtual void initialize() = 0;

        /// Drawing the state.
        virtual void draw() = 0;

        /// Updates the state by redrawing.
        virtual void update() = 0;

        /// Used for changing state.
        virtual void player_input() = 0;

        /// Inserting textures in sprite_sheets.
        static void load_state_sheets();

        /// Draws the high score in the window.
        virtual void create_high_score() = 0;

        ///
        static void extract_number_textures();

        /// Getters and setters.
        int get_high_score() const;
        void set_high_score( int score );
};

#endif