#include "Score.h"

void Score::calculate_score(int depth, ScoreType score_type)
{
    std::map<ScoreType, int> score_table{ {ScoreType::DIG, 5}, {ScoreType::KILLED_DEMODOG, 500}, {ScoreType::KILLED_DEMOGORGON, 1000},
                                          {ScoreType::ROCK_KILLED_DOG, 1000}, {ScoreType::ROCK_KILLED_GORGON, 2000},
                                          {ScoreType::EXTRA_POINT, 500},};

    std::map<int, double> bonus_table{ {0, 0}, {1, 0}, {2, 0.25}, {3, 0.50}, {4, 0.75} };

    int score{};

    if (score_type == ScoreType::DIG)
    {
        score = score_table[score_type];
    }
    else
    {
        score += score_table[score_type] + (score_table[score_type] * bonus_table[depth]);
    }

    PlayState::set_high_score(score);
}