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

// Bishop attacks
const int bishopDr[4] = {1, 1, -1, -1};
const int bishopDf[4] = {1, -1, 1, -1};

int startRank = square / 8;
int startFile = square % 8;

for(int dir = 0; dir < 4; dir++)
{
    int r = startRank + bishopDr[dir];
    int f = startFile + bishopDf[dir];

    while(r >= 0 && r < 8 &&
          f >= 0 && f < 8)
    {
        int sq = r * 8 + f;

        U64 mask = 1ULL << sq;

        if(attacker == WHITE)
        {
            if(board.bitboards[WB] & mask)
                return true;
        }
        else
        {
            if(board.bitboards[BB] & mask)
                return true;
        }

        if(board.occupancies[BOTH] & mask)
            break;

        r += bishopDr[dir];
        f += bishopDf[dir];
    }
}

// Rook attacks
const int rookDr[4] = {1, -1, 0, 0};
const int rookDf[4] = {0, 0, 1, -1};

for(int dir = 0; dir < 4; dir++)
{
    int r = startRank + rookDr[dir];
    int f = startFile + rookDf[dir];

    while(r >= 0 && r < 8 &&
          f >= 0 && f < 8)
    {
        int sq = r * 8 + f;

        U64 mask = 1ULL << sq;

        if(attacker == WHITE)
        {
            if(board.bitboards[WR] & mask)
                return true;
        }
        else
        {
            if(board.bitboards[BR] & mask)
                return true;
        }

        if(board.occupancies[BOTH] & mask)
            break;

        r += rookDr[dir];
        f += rookDf[dir];
    }
}

// Queen attacks
for(int dir = 0; dir < 8; dir++)
{
    const int queenDr[8] = {1, 1, -1, -1, 1, -1, 0, 0};
    const int queenDf[8] = {1, -1, 1, -1, 0, 0, 1, -1};

    int r = startRank + queenDr[dir];
    int f = startFile + queenDf[dir];

    while(r >= 0 && r < 8 &&
          f >= 0 && f < 8)
    {
        int sq = r * 8 + f;

        U64 mask = 1ULL << sq;

        if(attacker == WHITE)
        {
            if(board.bitboards[WQ] & mask)
                return true;
        }
        else
        {
            if(board.bitboards[BQ] & mask)
                return true;
        }

        if(board.occupancies[BOTH] & mask)
            break;

        r += queenDr[dir];
        f += queenDf[dir];
    }
}

if(attacker == WHITE)
{
    if(AttackTables::kingAttacks[square] &
       board.bitboards[WK])
    {
        return true;
    }
}
else
{
    if(AttackTables::kingAttacks[square] &
       board.bitboards[BK])
    {
        return true;
    }
}

    return false;
}
}