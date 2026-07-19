#pragma once

#include "Types.h"

namespace AttackTables
{
    extern U64 pawnAttacks[2][64];
    extern U64 knightAttacks[64];
    extern U64 kingAttacks[64];

    U64 MaskPawnAttacks(Side side, Square square);

    U64 MaskKnightAttacks(Square square);

    U64 MaskKingAttacks(Square square);

    void Initialize();
}