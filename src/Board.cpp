#include "Board.h"

#include <iostream>
#include <sstream>

Board::Board()
{
    Reset();
}

void Board::Reset()
{
    for (int piece = WP; piece <= BK; piece++)
        bitboards[piece] = 0ULL;

    occupancies[WHITE] = 0ULL;
    occupancies[BLACK] = 0ULL;
    occupancies[BOTH] = 0ULL;

    for (int square = A1; square <= H8; square++)
        pieceOnSquare[square] = NO_PIECE;

    side = WHITE;
    enPassant = NO_SQUARE;
    castling = 0;
    halfmoveClock = 0;
    fullmoveNumber = 1;
}

bool Board::LoadFEN(const std::string& fen)
{
    Reset();

    std::stringstream ss(fen);

    std::string boardPart;
    std::string sidePart;
    std::string castlePart;
    std::string epPart;

    ss >> boardPart;
    ss >> sidePart;
    ss >> castlePart;
    ss >> epPart;
    ss >> halfmoveClock;
    ss >> fullmoveNumber;

    int rank = 7;
    int file = 0;

    for(char c : boardPart)
    {
        if(c == '/')
        {
            rank--;
            file = 0;
            continue;
        }

        if(c >= '1' && c <= '8')
        {
            file += c - '0';
            continue;
        }

        Piece piece = NO_PIECE;

        switch(c)
        {
            case 'P': piece = WP; break;
            case 'N': piece = WN; break;
            case 'B': piece = WB; break;
            case 'R': piece = WR; break;
            case 'Q': piece = WQ; break;
            case 'K': piece = WK; break;

            case 'p': piece = BP; break;
            case 'n': piece = BN; break;
            case 'b': piece = BB; break;
            case 'r': piece = BR; break;
            case 'q': piece = BQ; break;
            case 'k': piece = BK; break;
        }

        if(piece != NO_PIECE)
        {
            int square = rank * 8 + file;

            pieceOnSquare[square] = piece;
            bitboards[piece] |= (1ULL << square);

            file++;
        }
    }

    side = (sidePart == "w") ? WHITE : BLACK;

    if(castlePart.find('K') != std::string::npos)
        castling |= WK_CASTLE;

    if(castlePart.find('Q') != std::string::npos)
        castling |= WQ_CASTLE;

    if(castlePart.find('k') != std::string::npos)
        castling |= BK_CASTLE;

    if(castlePart.find('q') != std::string::npos)
        castling |= BQ_CASTLE;

    if(epPart != "-")
    {
        int file = epPart[0] - 'a';
        int rank = epPart[1] - '1';

        enPassant = static_cast<Square>(rank * 8 + file);
    }

    for(int piece = WP; piece <= WK; piece++)
        occupancies[WHITE] |= bitboards[piece];

    for(int piece = BP; piece <= BK; piece++)
        occupancies[BLACK] |= bitboards[piece];

    occupancies[BOTH] =
        occupancies[WHITE] |
        occupancies[BLACK];

    return true;
}

bool Board::MakeMove(Move move)
{
    Square from = MoveEncoding::From(move);
    Square to   = MoveEncoding::To(move);

    Piece piece = MoveEncoding::PieceMoved(move);

    Piece captured = pieceOnSquare[to];

    bitboards[piece] &= ~(1ULL << from);

    bitboards[piece] |= (1ULL << to);

    pieceOnSquare[from] = NO_PIECE;

    pieceOnSquare[to] = piece;

    if(captured != NO_PIECE)
    {
        bitboards[captured] &= ~(1ULL << to);
    }

    occupancies[WHITE] = 0ULL;
    occupancies[BLACK] = 0ULL;

    for(int p = WP; p <= WK; p++)
        occupancies[WHITE] |= bitboards[p];

    for(int p = BP; p <= BK; p++)
        occupancies[BLACK] |= bitboards[p];

    occupancies[BOTH] =
        occupancies[WHITE] |
        occupancies[BLACK];

    side =
        side == WHITE ?
        BLACK :
        WHITE;

    return true;
}

Move Board::ParseMove(const std::string& moveText) const
{
    if(moveText.length() != 4)
        return 0;

    int fromFile = moveText[0] - 'a';
    int fromRank = moveText[1] - '1';

    int toFile = moveText[2] - 'a';
    int toRank = moveText[3] - '1';

    if(fromFile < 0 || fromFile > 7 ||
       toFile < 0 || toFile > 7 ||
       fromRank < 0 || fromRank > 7 ||
       toRank < 0 || toRank > 7)
    {
        return 0;
    }

    Square from =
        (Square)(fromRank * 8 + fromFile);

    Square to =
        (Square)(toRank * 8 + toFile);

    Piece piece = pieceOnSquare[from];

    if(piece == NO_PIECE)
        return 0;

    bool capture =
        pieceOnSquare[to] != NO_PIECE;

    return MoveEncoding::Encode(
        from,
        to,
        piece,
        NO_PIECE,
        capture
    );
}

void Board::Print() const
{
    const char pieceChar[] =
    {
        'P','N','B','R','Q','K',
        'p','n','b','r','q','k'
    };

    std::cout << '\n';

    for(int rank = 7; rank >= 0; rank--)
    {
        std::cout << rank + 1 << " ";

        for(int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;

            if(pieceOnSquare[square] == NO_PIECE)
                std::cout << ". ";
            else
                std::cout << pieceChar[pieceOnSquare[square]] << " ";
        }

        std::cout << '\n';
    }

    std::cout << "\n  A B C D E F G H\n\n";

    std::cout << "Side: "
              << (side == WHITE ? "White" : "Black")
              << '\n';

    std::cout << "Castling: ";

    if(castling == 0)
        std::cout << "-";

    if(castling & WK_CASTLE) std::cout << "K";
    if(castling & WQ_CASTLE) std::cout << "Q";
    if(castling & BK_CASTLE) std::cout << "k";
    if(castling & BQ_CASTLE) std::cout << "q";

    std::cout << '\n';

    std::cout << "En Passant: ";

    if(enPassant == NO_SQUARE)
        std::cout << "-";
    else
        std::cout << enPassant;

    std::cout << '\n';

    std::cout << "Halfmove: "
              << halfmoveClock
              << '\n';

    std::cout << "Fullmove: "
              << fullmoveNumber
              << "\n\n";
}