#pragma once

#include "Board.h"

namespace AttackDetector
{
    bool IsSquareAttacked(
        const Board& board,
        Square square,
        Side attacker
    );
}