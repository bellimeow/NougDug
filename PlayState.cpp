//
// Created by isade842 on 12/5/17.
//

#include "PlayState.h"
#include <iostream>
#include <fstream>
#include <string>

std::string AbstractGameState::directory;
std::string AbstractGameState::level;

PlayState::PlayState(Game* game)
        : game(game)
{
    directory = "/home/seblu114/TDP005/NougDug/";
    level = "level1.txt";
    path = directory + level;
    //load_game_board (")
    // board = new Board
}

int PlayState::get_player_lives()
{
    return 0;
}

void PlayState::player_input()
{

}

void PlayState::set_high_score()
{

}

void PlayState::intro_sequence()
{

}

std::ifstream PlayState::load_game_board(std::string filename) {
    std::ifstream level_data;
    level_data.open(filename, std::ifstream::in);

    if ( level_data.fail() )
    {
        std::cerr << "Couldn't open file!\n";
    }
    else
    {

        level_data >> board_height >> board_width;
        std::cout << board_height << " " << board_width << "\n";

        return level_data;
    }
}

void PlayState::check_state(){
    if (won())
    {
        game->win = true;
        change_state();
    }
    else if (lose())
    {
        change_state();
    }
}

bool PlayState::won()
{
    //return board->enemy_count == 0;
    return true;
}

bool PlayState::lose()
{
    return player_lives == 0;
}

void PlayState::change_state()
{
    //game->change_state(Endstate* , 2);
    std::cout << "StateChange\n";
}

void PlayState::draw()
{
    std::cout << "Blah" << "\n";
}

void PlayState::update()
{
    //std::cout << "Blah" << "\n";
}

void PlayState::initialize() {

    std::ifstream game_board{load_game_board (path)};
    std::ifstream* level_ptr{&game_board};
    board = new Board(level_ptr, board_width, board_height);
    std::cout << "Init" << "\n";
}

void PlayState::play_again() {
    std::cout << "Blah" << "\n";
}

int PlayState::get_high_score() {
    return 0;
}


