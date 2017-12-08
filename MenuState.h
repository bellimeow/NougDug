#ifndef MENUSTATE_H
#define MENUSTATE_H


#include "AbstractGameState.h"


class MenuState : public AbstractGameState
{
    private:
        Game* game;
        sf::RenderWindow* window_ptr;

    public:
        MenuState(Game* game, sf::RenderWindow* window_ptr);

        void draw() ;
        void update() ;
        void initialize() ;
        void play_again() ;
        void player_input() ;
        void change_state() ;
        void check_state() ;
        int get_high_score();
};

#endif