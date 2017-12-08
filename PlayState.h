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
        std::vector<AbstractGameState*> states{};
        Board* board;

        std::string path;


    public:
        int current_player_lives{};
        unsigned int board_width{};
        unsigned int board_height{};

        PlayState(Game* game);

        void player_input() ov;
        void intro_sequence();
        void set_high_score();
        std::ifstream load_game_board( std::string );
        void check_state();
        void change_state();
        bool won();
        bool lose();
        int get_player_lives();


        void draw() override;
        void update() override;
        void initialize() override;
        void play_again() override;
        int get_high_score() override;
};
#endif