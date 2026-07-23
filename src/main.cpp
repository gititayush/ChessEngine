// 
#include <iostream>

#include "AttackTables.h"
#include "Board.h"
#include "Perft.h"
#include "Bitboard.h"
int main()
{
    AttackTables::Initialize();

    Board board;

    board.LoadFEN("r3k2r/p1ppqpb1/bn2pnp1/2pP4/1p2P3/2N2N2/PPQBBPPP/R3K2R w KQkq - 0 1");

std::cout << "White Pawns   : " << Bitboard::CountBits(board.bitboards[WP]) << '\n';
std::cout << "White Knights : " << Bitboard::CountBits(board.bitboards[WN]) << '\n';
std::cout << "White Bishops : " << Bitboard::CountBits(board.bitboards[WB]) << '\n';
std::cout << "White Rooks   : " << Bitboard::CountBits(board.bitboards[WR]) << '\n';
std::cout << "White Queens  : " << Bitboard::CountBits(board.bitboards[WQ]) << '\n';
std::cout << "White King    : " << Bitboard::CountBits(board.bitboards[WK]) << '\n';

    board.Print();

    // for (int depth = 1; depth <= 5; depth++)
    // {
    //     std::cout << "Depth "
    //               << depth
    //               << " : "
    //               << Perft::Run(board, depth)
    //               << '\n';
    // }
    
    std::cout << "\n========== ROOT LEGAL MOVES ==========\n\n";

    Perft::Divide(board, 1);
    return 0;
}