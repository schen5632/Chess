#include "rook.h"
#include <string>

Rook::Rook(int row, int col, std::string piece, std::string colour, char symbol):
    Piece{row, col, "rook", colour, symbol} {}
Rook::~Rook() {}

void Rook::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();
    std::string oppositeColour;
    if (board[row][col]->getColour() == "black") {
        oppositeColour = "white";
    } else if (board[row][col]->getColour() == "white") {
        oppositeColour = "black";
    }

    // Searching for checks along the same row
    for (int i = col+1; i < 8; ++i) {
        if (board[row][i]->getColour() == oppositeColour) {
            setMoves(move{row, i, true});
            break;
        } else if (board[row][i]->getColour() == "none") {
            setMoves(move{row, i, false});
        } else {
            break;
        }
    }

    for (int i = col-1; i > -1; --i) {
        if (board[row][i]->getColour() == oppositeColour) {
            setMoves(move{row, i, true});
            break;
        } else if (board[row][i]->getColour() == "none") {
            setMoves(move{row, i, false});
        } else {
            break;
        }
    }

    // Searching for checks along the same column
    for (int i = row+1; i < 8; ++i) {
        if (board[i][col]->getColour() == oppositeColour) {
            setMoves(move{i, col, true});
            break;
        } else if (board[i][col]->getColour() == "none") {
            setMoves(move{i, col, false});
        } else {
            break;
        }
    }     

    for (int i = row-1; i > -1; --i) {
        if (board[i][col]->getColour() == oppositeColour) {
            setMoves(move{i, col, true});
            break;
        } else if (board[i][col]->getColour() == "none") {
            setMoves(move{i, col, false});
        } else {
            break;
        }
    } 
}