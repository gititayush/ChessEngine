#include "AttackDetector.h"

#include "AttackTables.h"
#include "Bitboard.h"

namespace AttackDetector
{

bool IsSquareAttacked(
    const Board& board,
    Square square,
    Side attacker
)
{
    if(attacker == WHITE)
    {
        if(AttackTables::pawnAttacks[BLACK][square] &
           board.bitboards[WP])
        {
            return true;
        }
    }
    else
    {
        if(AttackTables::pawnAttacks[WHITE][square] &
           board.bitboards[BP])
        {
            return true;
        }
    }
if(attacker == WHITE)
{
    if(AttackTables::knightAttacks[square] &
       board.bitboards[WN])
    {
        return true;
    }
}
else
{
    if(AttackTables::knightAttacks[square] &
       board.bitboards[BN])
    {
        return true;
    }
}
    return false;
}
}