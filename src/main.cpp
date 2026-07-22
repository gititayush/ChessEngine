#include <windows.h>

#include "AttackTables.h"
#include "Board.h"
#include "Perft.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    AttackTables::Initialize();

    Board board;

    board.LoadFEN(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    Perft::Divide(board, 6);

    /*
    while(true)
    {
        board.Print();

        std::string moveText;
        std::cin >> moveText;

        Move move = board.ParseMove(moveText);

        if(move == 0)
        {
            std::cout << "Invalid move!\n";
            continue;
        }

        UndoInfo undo;
        board.MakeMove(move, undo);
    }
    */

    return 0;
}