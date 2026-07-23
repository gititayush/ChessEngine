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


    if(depth == 0)
        return Evaluation::Evaluate(board);

    MoveList moves;
    MoveGenerator::Generate(board, moves);

    int legalMoves = 0;

    for(int i = 0; i < moves.count; i++)
    {
        Move move = moves.moves[i];

        UndoInfo undo;
        board.MakeMove(move, undo);

        Side mover = (board.side == WHITE) ? BLACK : WHITE;
        Square kingSquare = board.FindKing(mover);

        if(AttackDetector::IsSquareAttacked(board, kingSquare, board.side))
{

    board.UndoMove(move, undo);
    continue;
}

        legalMoves++;

        int score = -Negamax(
            board,
            depth - 1,
            ply + 1,
            -beta,
            -alpha);

        board.UndoMove(move, undo);

        if(score > alpha)
            alpha = score;

        if(alpha >= beta)
            break;
    }

    if(legalMoves == 0)
    {
        Square kingSquare = board.FindKing(board.side);

        if(AttackDetector::IsSquareAttacked(
                board,
                kingSquare,
                board.side == WHITE ? BLACK : WHITE))
        {
            return -MATE_SCORE + ply;
        }

        return 0;
    }

    return alpha;
}

Move FindBestMove(Board& board, int depth)
{
    MoveList moves;

    MoveGenerator::Generate(board, moves);

    MoveList legalMoveList;
    legalMoveList.count = 0;


    Move bestMove = 0;
    int bestScore = -INF;
    int legalMoves = 0;
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
        legalMoves++;
        legalMoveList.moves[legalMoveList.count++] = move;

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


if (legalMoves == 0)
{
    Square kingSquare = board.FindKing(board.side);

    std::cout << "\n========== GAME OVER ==========\n";

    if (AttackDetector::IsSquareAttacked(
            board,
            kingSquare,
            board.side == WHITE ? BLACK : WHITE))
    {
        std::cout << "Checkmate!\n";
    }
    else
    {
        std::cout << "Stalemate!\n";
    }

    std::cout << "No legal moves available.\n";

    return 0;
}

std::cout << "\nLegal moves:\n";

for (int i = 0; i < legalMoveList.count; i++)
{
    MoveEncoding::Print(legalMoveList.moves[i]);
    std::cout << '\n';
}

std::cout << '\n';

    std::cout << "\nBest Score = " << bestScore << '\n';

    return bestMove;
}

} // namespace Search