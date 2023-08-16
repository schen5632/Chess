#include "whitepawn.h"
#include "pawn.h"
#include "piece.h"
#include <string>
#include <memory>

WhitePawn::WhitePawn(int row, int col, std::string piece, std::string colour, char symbol):
    Pawn{row, col, piece, colour, symbol} {}

WhitePawn::~WhitePawn() {}

void WhitePawn::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();

    // Regular moves
    if (row+1 < 8 && board[row+1][col]->getColour() == "none") {
        setMoves(move{row+1, col, false});
        if (row+2 < 8 && board[row+2][col]->getColour() == "none" && getCount() == 0) {
            setMoves(move{row+2, col, false});
        }
    }

    // Captures
    if (row+1 < 8 && col+1 < 8 && board[row+1][col+1]->getColour() == "black") {
        setMoves(move{row+1, col+1, true});
    }

    if (row+1 < 8 && col-1 > -1 && board[row+1][col-1]->getColour() == "black") {
        setMoves(move{row+1, col-1, true});
    }

    // En Passant
    if (row == 4 && col-1 > -1 && board[row][col-1]->getSymbol() == 'p') {
        setMoves(move{row+1, col-1, true});
    }

    if (row == 4 && col+1 < 8 && board[row][col+1]->getSymbol() == 'p') {
        setMoves(move{row+1, col+1, true});
    }
}


