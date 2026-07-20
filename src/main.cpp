#include <iostream>

#include "AttackTables.h"
#include "Board.h"

int main()
{
    AttackTables::Initialize();

    Board board;

    board.LoadFEN(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    );

    while(true)
    {
        board.Print();

        std::string input;

        std::cout << "\nEnter Move (e2e4): ";

        std::cin >> input;

        if(input == "quit")
            break;

        Move move = board.ParseMove(input);

        if(move == 0)
        {
            std::cout << "\nInvalid Move\n\n";
            continue;
        }

        if(MoveGenerator::IsMoveLegal(board, move))
{
    board.MakeMove(move);
}
else
{
    std::cout << "\nIllegal Move!\n";
}
    }

    return 0;
}