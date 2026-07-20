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
GenerateBishopMoves(board, list);
GenerateRookMoves(board, list);
GenerateQueenMoves(board, list);
GenerateKingMoves(board, list);
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

void GenerateBishopMoves(const Board& board, MoveList& list)
{
    U64 bishops =
        board.side == WHITE ?
        board.bitboards[WB] :
        board.bitboards[BB];

    U64 friendly =
        board.side == WHITE ?
        board.occupancies[WHITE] :
        board.occupancies[BLACK];

    U64 enemy =
        board.side == WHITE ?
        board.occupancies[BLACK] :
        board.occupancies[WHITE];

    while(bishops)
    {
        int from = __builtin_ctzll(bishops);
        bishops &= bishops - 1;

        int startRank = from / 8;
        int startFile = from % 8;

        const int dr[4] = {1, 1, -1, -1};
        const int df[4] = {1, -1, 1, -1};

        for(int dir = 0; dir < 4; dir++)
        {
            int r = startRank + dr[dir];
            int f = startFile + df[dir];

            while(r >= 0 && r < 8 &&
                  f >= 0 && f < 8)
            {
                int to = r * 8 + f;

                U64 square = 1ULL << to;

                if(friendly & square)
                    break;

                bool capture = enemy & square;

                list.Add(
                    MoveEncoding::Encode(
                        (Square)from,
                        (Square)to,
                        board.side == WHITE ? WB : BB,
                        NO_PIECE,
                        capture
                    )
                );

                if(capture)
                    break;

                r += dr[dir];
                f += df[dir];
            }
        }
    }
}

void GenerateRookMoves(const Board& board, MoveList& list)
{
    U64 rooks =
        board.side == WHITE ?
        board.bitboards[WR] :
        board.bitboards[BR];

    U64 friendly =
        board.side == WHITE ?
        board.occupancies[WHITE] :
        board.occupancies[BLACK];


    U64 enemy =
        board.side == WHITE ?
        board.occupancies[BLACK] :
        board.occupancies[WHITE];

    while(rooks)
    {
        int from = __builtin_ctzll(rooks);
        rooks &= rooks - 1;

        int startRank = from / 8;
        int startFile = from % 8;

        const int dr[4] = {1, -1, 0, 0};
        const int df[4] = {0, 0, 1, -1};

        for(int dir = 0; dir < 4; dir++)
        {
            int r = startRank + dr[dir];
            int f = startFile + df[dir];

            while(r >= 0 && r < 8 &&
                  f >= 0 && f < 8)
            {
                int to = r * 8 + f;

                U64 square = 1ULL << to;
                if(friendly & square)
{
    break;
}

                bool capture = enemy & square;

                list.Add(
                    MoveEncoding::Encode(
                        (Square)from,
                        (Square)to,
                        board.side == WHITE ? WR : BR,
                        NO_PIECE,
                        capture
                    )
                );

                if(capture)
                    break;

                r += dr[dir];
                f += df[dir];
            }
        }
    }
}
void GenerateQueenMoves(const Board& board, MoveList& list)
{
    U64 queens =
        board.side == WHITE ?
        board.bitboards[WQ] :
        board.bitboards[BQ];

    U64 friendly =
        board.side == WHITE ?
        board.occupancies[WHITE] :
        board.occupancies[BLACK];

    U64 enemy =
        board.side == WHITE ?
        board.occupancies[BLACK] :
        board.occupancies[WHITE];

    const int dr[8] = {1, 1, -1, -1, 1, -1, 0, 0};
    const int df[8] = {1, -1, 1, -1, 0, 0, 1, -1};

    while(queens)
    {
        int from = __builtin_ctzll(queens);
        queens &= queens - 1;

        int startRank = from / 8;
        int startFile = from % 8;

        for(int dir = 0; dir < 8; dir++)
        {
            int r = startRank + dr[dir];
            int f = startFile + df[dir];

            while(r >= 0 && r < 8 &&
                  f >= 0 && f < 8)
            {
                int to = r * 8 + f;

                U64 square = 1ULL << to;

                if(friendly & square)
                    break;

                bool capture = (enemy & square);

                list.Add(
                    MoveEncoding::Encode(
                        (Square)from,
                        (Square)to,
                        board.side == WHITE ? WQ : BQ,
                        NO_PIECE,
                        capture
                    )
                );

                if(capture)
                    break;

                r += dr[dir];
                f += df[dir];
            }
        }
    }
}

void GenerateKingMoves(const Board& board, MoveList& list)
{
    U64 kings =
        board.side == WHITE ?
        board.bitboards[WK] :
        board.bitboards[BK];

    U64 friendly =
        board.side == WHITE ?
        board.occupancies[WHITE] :
        board.occupancies[BLACK];

    U64 enemy =
        board.side == WHITE ?
        board.occupancies[BLACK] :
        board.occupancies[WHITE];

    while(kings)
    {
        int from = __builtin_ctzll(kings);
        kings &= kings - 1;

        U64 attacks =
            AttackTables::kingAttacks[from] &
            ~friendly;

        while(attacks)
        {
            int to = __builtin_ctzll(attacks);

            attacks &= attacks - 1;

            bool capture =
                (enemy & (1ULL << to));

            list.Add(
                MoveEncoding::Encode(
                    (Square)from,
                    (Square)to,
                    board.side == WHITE ? WK : BK,
                    NO_PIECE,
                    capture
                )
            );
        }
    }
}

bool IsMoveLegal(const Board& board, Move move)
{
    MoveList list;

    Generate(board, list);

    for(int i = 0; i < list.count; i++)
    {
        if(list.moves[i] == move)
            return true;
    }

    return false;
}
}