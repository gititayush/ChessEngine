#include "MoveGenerator.h"

#include "AttackTables.h"
#include "Bitboard.h"

namespace MoveGenerator
{

void Generate(const Board& board, MoveList& list)
{
    list.Clear();

    if(board.side == WHITE)
    {
        GenerateWhitePawnMoves(board, list);
    }
    else
    {
        GenerateBlackPawnMoves(board, list);
    }

    GenerateKnightMoves(board, list);
}

void GenerateWhitePawnMoves(const Board& board, MoveList& list)
{
    U64 pawns = board.bitboards[WP];

    while(pawns)
    {
        int from = __builtin_ctzll(pawns);

        pawns &= pawns - 1;

        int to = from + 8;

        if(to <= H8 &&
           !(board.occupancies[BOTH] & (1ULL << to)))
        {
            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)to,
                    WP
                )
            );

            if(from >= A2 &&
               from <= H2)
            {
                int doublePush = from + 16;

                if(!(board.occupancies[BOTH] &
                     (1ULL << doublePush)))
                {
                    list.Add(
                        MoveEncoding::Encode(
                            (Square)from,
                            (Square)doublePush,
                            WP,
                            NO_PIECE,
                            false,
                            true
                        )
                    );
                }
            }
        }

        U64 attacks =
            AttackTables::pawnAttacks[WHITE][from]
            &
            board.occupancies[BLACK];

        while(attacks)
        {
            int target = __builtin_ctzll(attacks);

            attacks &= attacks - 1;

            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)target,
                    WP,
                    NO_PIECE,
                    true
                )
            );
        }
    }
}

void GenerateBlackPawnMoves(const Board& board, MoveList& list)
{
    U64 pawns = board.bitboards[BP];

    while(pawns)
    {
        int from = __builtin_ctzll(pawns);

        pawns &= pawns - 1;

        int to = from - 8;

        if(to >= A1 &&
           !(board.occupancies[BOTH] & (1ULL << to)))
        {
            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)to,
                    BP
                )
            );

            if(from >= A7 &&
               from <= H7)
            {
                int doublePush = from - 16;

                if(!(board.occupancies[BOTH] &
                     (1ULL << doublePush)))
                {
                    list.Add(
                        MoveEncoding::Encode(
                            (Square)from,
                            (Square)doublePush,
                            BP,
                            NO_PIECE,
                            false,
                            true
                        )
                    );
                }
            }
        }

        U64 attacks =
            AttackTables::pawnAttacks[BLACK][from]
            &
            board.occupancies[WHITE];

        while(attacks)
        {
            int target = __builtin_ctzll(attacks);

            attacks &= attacks - 1;

            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)target,
                    BP,
                    NO_PIECE,
                    true
                )
            );
        }
    }
}

void GenerateKnightMoves(const Board& board, MoveList& list)
{
    U64 knights =
        board.side == WHITE ?
        board.bitboards[WN] :
        board.bitboards[BN];

    U64 friendly =
        board.side == WHITE ?
        board.occupancies[WHITE] :
        board.occupancies[BLACK];

    while(knights)
    {
        int from = __builtin_ctzll(knights);

        knights &= knights - 1;

        U64 attacks =
            AttackTables::knightAttacks[from]
            &
            ~friendly;

        while(attacks)
        {
            int to = __builtin_ctzll(attacks);

            attacks &= attacks - 1;

            bool capture =
                board.occupancies[
                    board.side == WHITE ?
                    BLACK :
                    WHITE
                ] &
                (1ULL << to);

            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)to,
                    board.side == WHITE ? WN : BN,
                    NO_PIECE,
                    capture
                )
            );
        }
    }
}

}