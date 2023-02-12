#ifndef SCORE_H
#define SCORE_H

#include "Board.h"
#include "ScoreType.h"

/** Class to handle score in the game
 *
 *
 */

class Score
{
    private:


    public:

        /// Calculates score based on depth and ScoreType
        static void calculate_score ( int depth, ScoreType );
};

#endif
