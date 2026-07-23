#include "Search.h"

#include <iostream>

#include "AttackDetector.h"
#include "Evaluation.h"
#include "MoveGenerator.h"

namespace Search
{

constexpr int INF = 1000000;
constexpr int MATE_SCORE = 30000;

int Negamax(
    Board& board,
    int depth,
    int ply,
    int alpha,
    int beta)
{
    if (depth == 0)
        return Evaluation::Evaluate(board);

    MoveList moves;
    MoveGenerator::Generate(board, moves);

    if (moves.count == 0)
    {
        Square kingSquare = board.FindKing(board.side);

        if (AttackDetector::IsSquareAttacked(
                board,
                kingSquare,
                board.side == WHITE ? BLACK : WHITE))
        {
            return -MATE_SCORE + ply;
        }

        return 0;
    }

    for (int i = 0; i < moves.count; i++)
    {
        Move move = moves.moves[i];

        UndoInfo undo;

        board.MakeMove(move, undo);

        if (depth == 2)
{
    MoveEncoding::Print(move);
    std::cout << '\n';
}

        Side mover = (board.side == WHITE) ? BLACK : WHITE;
        Square kingSquare = board.FindKing(mover);

        if (AttackDetector::IsSquareAttacked(board, kingSquare, board.side))
        {
            board.UndoMove(move, undo);
            continue;
        }

        int score = -Negamax(
            board,
            depth - 1,
            ply + 1,
            -beta,
            -alpha);

        board.UndoMove(move, undo);

        if (score > alpha)
            alpha = score;

        if (alpha >= beta)
            break;
    }

    return alpha;
}

Move FindBestMove(Board& board, int depth)
{
    MoveList moves;
    MoveGenerator::Generate(board, moves);

    Move bestMove = 0;
    int bestScore = -INF;

    for (int i = 0; i < moves.count; i++)
    {
        Move move = moves.moves[i];

        UndoInfo undo;

        board.MakeMove(move, undo);

        Side mover = (board.side == WHITE) ? BLACK : WHITE;
        Square kingSquare = board.FindKing(mover);

        if (AttackDetector::IsSquareAttacked(board, kingSquare, board.side))
        {
            board.UndoMove(move, undo);
            continue;
        }

        // DEBUG: Print board after Qxe4
        if (MoveEncoding::From(move) == E2 &&
            MoveEncoding::To(move) == E4)
        {
            std::cout << "\n===== BOARD AFTER e2e4 =====\n";
            board.Print();
        }

        int score = -Negamax(
            board,
            depth - 1,
            1,
            -INF,
            INF);

        board.UndoMove(move, undo);

        MoveEncoding::Print(move);
        std::cout << "  Search Score = " << score << '\n';

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    std::cout << "\nBest Score = " << bestScore << '\n';

    return bestMove;
}

} // namespace Search