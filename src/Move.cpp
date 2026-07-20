#include "Move.h"

#include <iostream>

namespace MoveEncoding
{

Move Encode(
    Square from,
    Square to,
    Piece piece,
    Piece promotion,
    bool capture,
    bool doublePush,
    bool enPassant,
    bool castling)
{
    Move move = 0;

    move |= from;

    move |= (to << 6);

    move |= (piece << 12);

    move |= (promotion << 16);

    if(capture)
        move |= (1 << 20);

    if(doublePush)
        move |= (1 << 21);

    if(enPassant)
        move |= (1 << 22);

    if(castling)
        move |= (1 << 23);

    return move;
}

Square From(Move move)
{
    return Square(move & 0x3F);
}

Square To(Move move)
{
    return Square((move >> 6) & 0x3F);
}

Piece PieceMoved(Move move)
{
    return Piece((move >> 12) & 0xF);
}

Piece PromotionPiece(Move move)
{
    return Piece((move >> 16) & 0xF);
}

bool IsCapture(Move move)
{
    return move & (1 << 20);
}

bool IsDoublePush(Move move)
{
    return move & (1 << 21);
}

bool IsEnPassant(Move move)
{
    return move & (1 << 22);
}

bool IsCastling(Move move)
{
    return move & (1 << 23);
}

void Print(Move move)
{
    auto printSquare = [](Square sq)
    {
        char file = 'a' + (sq % 8);
        char rank = '1' + (sq / 8);

        std::cout << file << rank;
    };

    printSquare(From(move));

    printSquare(To(move));

    if(PromotionPiece(move) != NO_PIECE)
    {
        const char promo[] =
        {
            'p','n','b','r','q','k',
            'p','n','b','r','q','k'
        };

        std::cout << promo[PromotionPiece(move)];
    }

    std::cout << '\n';
}

}