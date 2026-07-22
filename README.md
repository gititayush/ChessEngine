# KnightShift

A chess engine written from scratch in modern C++.

## Features

- Bitboard-based board representation
- FEN parsing
- Legal move generation
- Castling
- En passant
- Pawn promotion
- Promotion captures
- Check detection
- MakeMove / UndoMove
- Perft testing
- UCI interface (in progress)

## Perft Results

| Depth | Nodes |
|------:|-------------:|
| 1 | 20 |
| 2 | 400 |
| 3 | 8,902 |
| 4 | 197,281 |
| 5 | 4,865,609 |
| 6 | 119,060,324 |

Verified against the official Chess Programming Wiki perft values.

## Tech Stack

- C++17
- CMake
- Bitboards
- VS Code

## Roadmap

- [x] Bitboards
- [x] Move generation
- [x] Legal move validation
- [x] Castling
- [x] En passant
- [x] Promotions
- [x] Perft
- [ ] Evaluation
- [ ] Negamax
- [ ] Alpha-Beta Pruning
- [ ] Move Ordering
- [ ] Quiescence Search
- [ ] Transposition Tables
- [ ] Iterative Deepening
- [ ] UCI Support
- [ ] Piece-Square Tables

## Author

Built by Ayush.
