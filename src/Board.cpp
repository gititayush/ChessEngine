#include "Board.h"

#include <iostream>

Board::Board()
{
    Reset();
}

void Board::Reset()
{
    // Clear piece bitboards
    for (int piece = WP; piece <= BK; piece++)
        bitboards[piece] = 0ULL;

    // Clear occupancies
    occupancies[WHITE] = 0ULL;
    occupancies[BLACK] = 0ULL;
    occupancies[BOTH] = 0ULL;

    // Clear square array
    for (int square = A1; square <= H8; square++)
        pieceOnSquare[square] = NO_PIECE;

    side = WHITE;

    enPassant = NO_SQUARE;

    castling = 0;

    halfmoveClock = 0;

    fullmoveNumber = 1;
}

bool Board::LoadFEN(const std::string& fen)
{
    Reset();

    return true;
}

void Board::Print() const
{
    const char pieceChar[] =
    {
        'P','N','B','R','Q','K',
        'p','n','b','r','q','k'
    };

    std::cout << '\n';

    for (int rank = 7; rank >= 0; rank--)
    {
        std::cout << rank + 1 << "  ";

        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;

            if (pieceOnSquare[square] == NO_PIECE)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << pieceChar[pieceOnSquare[square]] << " ";
            }
        }

        std::cout << '\n';
    }

    std::cout << "\n   A B C D E F G H\n\n";
}