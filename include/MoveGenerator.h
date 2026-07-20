#pragma once

#include "Board.h"
#include "MoveList.h"

namespace MoveGenerator
{
    void Generate(const Board& board, MoveList& list);

    void GenerateWhitePawnMoves(const Board& board, MoveList& list);
    void GenerateBlackPawnMoves(const Board& board, MoveList& list);

    void GenerateKnightMoves(const Board& board, MoveList& list);

    bool IsMoveLegal(
        const Board& board,
        Move move
    );
}