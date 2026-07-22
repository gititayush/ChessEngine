#pragma once

#include "Board.h"

namespace Perft
{
    U64 Run(Board& board, int depth);

    void Divide(Board& board, int depth);
}