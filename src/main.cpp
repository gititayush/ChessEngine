#include "Board.h"

int main()
{
    Board board;

    board.LoadFEN(
        "8/8/8/8/8/8/8/8 w - - 0 1"
    );

    board.Print();

    return 0;
}