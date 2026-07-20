#pragma once

#include "Move.h"

struct MoveList
{
    Move moves[256];

    int count;

    MoveList();

    void Clear();

    void Add(Move move);

    void Print() const;
};