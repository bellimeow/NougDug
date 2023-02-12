#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <fstream>
#include "AbstractGameState.h"
#include "Board.h"

class Board;

/** Class to handle the state of the game being played
 *  I checks for input, victory, losing, switching level, players lives
 *  and keeps the board, which hold all objects
 */

class PlayState : public AbstractGameState
{
    private:
        Game* game; /// Pointer back to the game that created it
        sf::RenderWindow* window_ptr; /// Pointer to the window, to avoid multiple windows
        Board* board; /// Pointer to the board it creates
        int level_num { 1 }; /// Number representing current level, used to load level

        std::string path; /// Path to current level file

    public:

        int current_player_lives {};
        unsigned int board_width{};
        unsigned int board_height{};

        ///Constructor, takes Game pointer and ReinderWindow pointer
        PlayState(Game* game, sf::RenderWindow* window_ptr);

        /// Destructor to clean up
        ~PlayState();

        /// Function to handle input from the player
        void player_input() override;

        /// Currently Unused
        void intro_sequence();

        /// Loads the board from file to file stream
        std::ifstream load_game_board( std::string );

        /// Checks state to se if change i needed
        void check_state() override;

        /// Tells game to change state
        void change_state() override;

        /// Check if game is won
        bool won();

        /// Check if game is lost
        bool lose();

        /// Getter current:player_lives, unused
        int get_player_lives();

        /// Draw, calls draw in board
        void draw() override;

        /// Updates board
        void update() override;

        /// Initializes playstate, creating a new board from the level file
        void initialize() override;

        /// Currently unused
        void play_again() ;

        /// Draws high score
        void create_high_score() override;

        /// Static setter, high_score
        static void set_high_score(int score);

        /// Chacks and draws players lives
        void display_player_lives();
};

#endif