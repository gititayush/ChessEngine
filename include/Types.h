#pragma once

#include <cstdint>

// Integer aliases
using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;


// ===========================
// Squares
// ===========================

enum Square
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,

    NO_SQUARE
};


// ===========================
// Sides
// ===========================

enum Side
{
    WHITE,
    BLACK,
    BOTH
};


// ===========================
// Pieces
// ===========================

enum Piece
{
    WP, WN, WB, WR, WQ, WK,
    BP, BN, BB, BR, BQ, BK,

    NO_PIECE
};


// ===========================
// Castling Rights
// ===========================

enum Castling
{
    WK_CASTLE = 1,
    WQ_CASTLE = 2,
    BK_CASTLE = 4,
    BQ_CASTLE = 8
};