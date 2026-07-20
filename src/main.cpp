#include "Board.h"

int main()
{
    Board board;

    board.LoadFEN(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    );

    board.Print();

    return 0;
}