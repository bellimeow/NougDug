#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
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

public:
    int player_lives{};

    PlayState(Game* game);

    void player_input();
    void intro_sequence();
    void check_state();
    void change_state();
    bool won();
    bool lose();

    int get_player_lives();
    void set_high_score();

    void draw() override;
    void update() override;
    void initialize() override;
    void play_again() override;
    int get_high_score() override;
};
#endif