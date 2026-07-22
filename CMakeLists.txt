cmake_minimum_required(VERSION 3.20)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    ChessEngine
    src/main.cpp
    src/Bitboard.cpp
    src/AttackTables.cpp
    src/Board.cpp
    src/Move.cpp
    src/FEN.cpp
    src/Search.cpp
    src/Evaluation.cpp
    src/UCI.cpp
    src/MoveList.cpp
    src/MoveGenerator.cpp
    src/AttackDetector.cpp
    src/Perft.cpp
)

target_include_directories(
    ChessEngine
    PRIVATE
    include
)