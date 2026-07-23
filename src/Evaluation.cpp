#include "Evaluation.h"
#include "Bitboard.h"

namespace Evaluation
{
    constexpr int PieceValues[] =
    {
        100, // Pawn
        320, // Knight
        330, // Bishop
        500, // Rook
        900, // Queen
        0    // King
    };

    constexpr int PIECE_TYPES = sizeof(PieceValues) / sizeof(PieceValues[0]);

    int Evaluate(const Board& board)
    {
        int score = 0;

        // White material
        for (int piece = WP; piece <= WK; piece++)
        {
            score += Bitboard::CountBits(board.bitboards[piece]) * PieceValues[piece];
        }

        // Black material
        for (int piece = BP; piece <= BK; piece++)
        {
            score -= Bitboard::CountBits(board.bitboards[piece]) *
                     PieceValues[piece - PIECE_TYPES];
        }

return (board.side == WHITE) ? score : -score;    }
}