// 
#include <iostream>

#include "AttackTables.h"
#include "Board.h"
#include "Perft.h"
#include "Bitboard.h"
int main()
{
    AttackTables::Initialize();

    Bitboard::Print(AttackTables::knightAttacks[E5]);

    Board board;

    board.LoadFEN("r3k2r/p1ppqpb1/bn2pnp1/2pP4/1p2P3/2N2N2/PPQBBPPP/R3K2R w KQkq - 0 1");

    board.Print();

    // for (int depth = 1; depth <= 6; depth++)
    // {
    //     std::cout << "Depth "
    //               << depth
    //               << " : "
    //               << Perft::Run(board, depth)
    //               << '\n';
    // }

    Perft::Divide(board, 2);

    return 0;
}