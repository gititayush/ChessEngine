#pragma once

#include "Board.h"
#include "Move.h"

namespace Search
{
    Move FindBestMove(Board& board, int depth);

    int Negamax(
        Board& board,
        int depth,
        int ply,
        int alpha,
        int beta
    );
}