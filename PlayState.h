#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <fstream>
#include "AbstractGameState.h"
#include "Board.h"

class Board;

class PlayState : public AbstractGameState
{
    private:
        int high_score{};
        Game* game;
        sf::RenderWindow* window_ptr;
        std::vector<AbstractGameState*> states{};
        Board* board;

        std::string path;


    public:
        int current_player_lives{};
        unsigned int board_width{};
        unsigned int board_height{};

        PlayState(Game* game, sf::RenderWindow* window_ptr);

        void player_input() ;
        void intro_sequence();
        void set_high_score();
        std::ifstream load_game_board( std::string );
        void check_state();
        void change_state();
        bool won();
        bool lose();
        int get_player_lives();


        void draw();
        void update() ;
        void initialize() ;
        void play_again() ;
        int get_high_score();
};

#endif