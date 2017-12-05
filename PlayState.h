#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include "AbstractGameState.h"


class PlayState : AbstractGameState
{
private:
    int high_score{};
    Game* game;
    std::vector<AbstractGameState*> states{PlayState*};
    //Board board;

public:
    int player_lives{};

    PlayState(Game *game);

    void player_input();
    void intro_sequence();
    void check_state();
    void change_state();
    bool won();
    bool lose();

    int get_player_lives();
    void set_high_score();
};
#endif