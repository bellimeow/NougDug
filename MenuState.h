#ifndef MENUSTATE_H
#define MENUSTATE_H


#include "AbstractGameState.h"


class MenuState : public AbstractGameState
{
    private:

        Game* game; /// pointer to game that made it
        sf::RenderWindow* window_ptr; /// render window pointer to draw

    public:

        /// Constructor
        MenuState(Game* game, sf::RenderWindow* window_ptr);

        /// Draws everything in the menu
        void draw() override;

        /// Calls draw
        void update() override;

        /// Calls Change state
        void player_input() override;

        /// Changes state to playstate, i.e.  state 1
        void change_state() override;

        /// These functions are not yet implemented.
        void initialize() override;
        void check_state() override ;
        void create_high_score() override;
    };

#endif