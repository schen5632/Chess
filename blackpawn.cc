#include "blackpawn.h"
#include <string>

BlackPawn::BlackPawn(int row, int col, std::string piece, std::string colour, char symbol):
    Pawn{row, col, piece, colour, symbol} {}

BlackPawn::~BlackPawn() {}

void BlackPawn::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();

    // regular moves 
    if (row-1 > -1 && board[row-1][col]->getColour() == "none") {
        setMoves(move{row-1, col, false});
        if (row-2 > -1 && board[row-2][col]->getColour() == "none" && getCount() == 0) {
            setMoves(move{row-2, col, false});
        }
    }

    // captures
    if (row-1 > -1 && col+1 < 8 && board[row-1][col+1]->getColour() == "white") {
        setMoves(move{row-1, col+1, true});
    }

    if (row-1 > -1 && col-1 > -1 && board[row-1][col-1]->getColour() == "white") {
        setMoves(move{row-1, col-1, true});
    }

    // en passant
    if (row == 3 && col-1 > -1 && board[row][col-1]->getSymbol() == 'P') {
        setMoves(move{row-1, col-1, true});
    }

    if (row == 3 && col+1 < 8 && board[row][col+1]->getSymbol() == 'P') {
        setMoves(move{row-1, col+1, true});
    }
}
