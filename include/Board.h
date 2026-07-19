#pragma once

#include <string>

#include "Types.h"

class Board
{
public:

    // Piece bitboards
    U64 bitboards[12];

    // White, Black, Both
    U64 occupancies[3];

    // Piece on every square
    Piece pieceOnSquare[64];

    // Side to move
    Side side;

    // En passant square
    Square enPassant;

    // Castling rights
    int castling;

    // 50 move rule
    int halfmoveClock;

    // Move number
    int fullmoveNumber;

    Board();

    void Reset();

    bool LoadFEN(const std::string& fen);

    void Print() const;
};