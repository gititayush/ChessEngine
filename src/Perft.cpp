#include "Perft.h"
#include "MoveGenerator.h"

#include <iostream>

namespace Perft
{

U64 Run(Board& board, int depth)
{
    if(depth == 0)
        return 1;

    MoveList list;
    MoveGenerator::Generate(board, list);

    U64 nodes = 0;

    for(int i = 0; i < list.count; i++)
    {
        Move move = list.moves[i];

        if(!MoveGenerator::IsMoveLegal(board, move))
            continue;

        UndoInfo undo;

        board.MakeMove(move, undo);

        nodes += Run(board, depth - 1);

        board.UndoMove(move, undo);
    }

    return nodes;
}
void Divide(Board& board, int depth)
{
    MoveList list;
    MoveGenerator::Generate(board, list);

    U64 total = 0;

    for(int i = 0; i < list.count; i++)
    {
        Move move = list.moves[i];

        if(!MoveGenerator::IsMoveLegal(board, move))
            continue;

        UndoInfo undo;

        board.MakeMove(move, undo);

        U64 nodes = Run(board, depth - 1);

        board.UndoMove(move, undo);

        total += nodes;

        std::cout
            << MoveEncoding::SquareToString(MoveEncoding::From(move))
            << MoveEncoding::SquareToString(MoveEncoding::To(move));

        Piece promo = MoveEncoding::PromotionPiece(move);

        if(promo != NO_PIECE)
        {
            switch(promo)
            {
                case WQ:
                case BQ: std::cout << "q"; break;

                case WR:
                case BR: std::cout << "r"; break;

                case WB:
                case BB: std::cout << "b"; break;

                case WN:
                case BN: std::cout << "n"; break;

                default: break;
            }
        }

        std::cout << " : " << nodes << '\n';
    }

    std::cout << "\nTotal nodes = "
              << total
              << "\n";
}

}