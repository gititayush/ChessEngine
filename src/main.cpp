#include "MoveList.h"

int main()
{
    MoveList list;

    list.Add(
        MoveEncoding::Encode(
            E2,
            E4,
            WP,
            NO_PIECE,
            false,
            true,
            false,
            false
        )
    );

    list.Add(
        MoveEncoding::Encode(
            G1,
            F3,
            WN
        )
    );

    list.Add(
        MoveEncoding::Encode(
            B1,
            C3,
            WN
        )
    );

    list.Print();

    return 0;
}