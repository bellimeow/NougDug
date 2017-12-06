//
// Created by isade842 on 12/5/17.
//

#include "PlayState.h"


PlayState::PlayState(Game* game) : game(game)
{

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
    return board->enemy_count == 0;
}

bool PlayState::lose()
{
    return player_lives == 0;
}

void PlayState::change_state()
{
    game->change_state(Endstate*, 2);
}
