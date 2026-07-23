#include "AttackTables.h"
#include "Bitboard.h"

U64 AttackTables::pawnAttacks[2][64];

U64 AttackTables::knightAttacks[64];

U64 AttackTables::kingAttacks[64];

U64 AttackTables::MaskPawnAttacks(Side side, Square square)
{
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    bitboard |= (1ULL << square);

    if (side == WHITE)
    {
        if ((bitboard << 7) & Bitboard::NOT_H_FILE)
            attacks |= (bitboard << 7);

        if ((bitboard << 9) & Bitboard::NOT_A_FILE)
            attacks |= (bitboard << 9);
    }
    else
    {
        if ((bitboard >> 7) & Bitboard::NOT_A_FILE)
            attacks |= (bitboard >> 7);

        if ((bitboard >> 9) & Bitboard::NOT_H_FILE)
            attacks |= (bitboard >> 9);
    }

    return attacks;
}

U64 AttackTables::MaskKnightAttacks(Square square)
{
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    bitboard |= (1ULL << square);

    if ((bitboard >> 17) & Bitboard::NOT_H_FILE)
        attacks |= (bitboard >> 17);

    if ((bitboard >> 15) & Bitboard::NOT_A_FILE)
        attacks |= (bitboard >> 15);

    if ((bitboard >> 10) & Bitboard::NOT_GH_FILE)
        attacks |= (bitboard >> 10);

    if ((bitboard >> 6) & Bitboard::NOT_AB_FILE)
        attacks |= (bitboard >> 6);

    if ((bitboard << 17) & Bitboard::NOT_A_FILE)
        attacks |= (bitboard << 17);

    if ((bitboard << 15) & Bitboard::NOT_H_FILE)
        attacks |= (bitboard << 15);

    if ((bitboard << 10) & Bitboard::NOT_AB_FILE)
        attacks |= (bitboard << 10);

    if ((bitboard << 6) & Bitboard::NOT_GH_FILE)
        attacks |= (bitboard << 6);

    return attacks;
}

U64 AttackTables::MaskKingAttacks(Square square)
{
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    bitboard |= (1ULL << square);

    if ((bitboard >> 8))
        attacks |= (bitboard >> 8);

    if ((bitboard << 8))
        attacks |= (bitboard << 8);

    if ((bitboard >> 1) & Bitboard::NOT_H_FILE)
        attacks |= (bitboard >> 1);

    if ((bitboard << 1) & Bitboard::NOT_A_FILE)
        attacks |= (bitboard << 1);

    if ((bitboard >> 9) & Bitboard::NOT_H_FILE)
        attacks |= (bitboard >> 9);

    if ((bitboard >> 7) & Bitboard::NOT_A_FILE)
        attacks |= (bitboard >> 7);

    if ((bitboard << 9) & Bitboard::NOT_A_FILE)
        attacks |= (bitboard << 9);

    if ((bitboard << 7) & Bitboard::NOT_H_FILE)
        attacks |= (bitboard << 7);

    return attacks;
}

void AttackTables::Initialize()
{
    for (int square = A1; square <= H8; square++)
    {
        pawnAttacks[WHITE][square] =
            MaskPawnAttacks(WHITE, static_cast<Square>(square));

        pawnAttacks[BLACK][square] =
            MaskPawnAttacks(BLACK, static_cast<Square>(square));

        knightAttacks[square] =
            MaskKnightAttacks(static_cast<Square>(square));

        kingAttacks[square] =
            MaskKingAttacks(static_cast<Square>(square));
    }
}
