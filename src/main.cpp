#include <windows.h>
#include <iostream>

#include "AttackTables.h"
#include "Board.h"
#include "Search.h"
#include "Move.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    AttackTables::Initialize();

    Board board;

    board.LoadFEN(
        "8/8/8/8/4q3/8/4Q3/4K3 w - - 0 1");

    board.Print();

    Move bestMove = Search::FindBestMove(board, 3);

    std::cout << "\n\nBest Move: ";
    MoveEncoding::Print(bestMove);
    std::cout << '\n';

    return 0;
}