#ifndef ENDSTATE_H
#define ENDSTATE_H


#include "AbstractGameState.h"

/** Handles what the player sees when they lose or win
 * and allow replaying the game
 */


class EndState : public AbstractGameState
{
    private:
        Game* game; /// Pointer to game that created it
        sf::RenderWindow* window_ptr; /// Pointer to window to drw stuff

    public:

        /// Constructor, like other states
        EndState(Game* game, sf::RenderWindow* window_ptr);

        /// Draws the end state
        void draw() override;

        /// Calls draw
        void update() override;

        /// Not implemented
        void initialize() override;
        void play_again() ;
        void check_state() override;

        /// Replays the game on player input
        void player_input() override;

        /// Tells game to change state
        void change_state() override;

        /// Draws the high score
        void create_high_score() override;
};

#endif