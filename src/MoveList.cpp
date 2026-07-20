#include "MoveList.h"

#include <iostream>

MoveList::MoveList()
{
    count = 0;
}

void MoveList::Clear()
{
    count = 0;
}

void MoveList::Add(Move move)
{
    moves[count++] = move;
}

void MoveList::Print() const
{
    std::cout << "\nMove List\n";
    std::cout << "-----------------\n";

    for(int i = 0; i < count; i++)
    {
        std::cout << i + 1 << ". ";

        MoveEncoding::Print(moves[i]);
    }

    std::cout << "\nTotal Moves : "
              << count
              << "\n\n";
}