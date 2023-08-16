#include "queen.h"
#include <string>

Queen::Queen(int row, int col, std::string piece, std::string colour, char symbol):
    Piece{row, col, "queen", colour, symbol} {}

Queen::~Queen() {}

void Queen::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();
    std::string oppositeColour;
    if (board[row][col]->getColour() == "black") {
        oppositeColour = "white";
    } else if (board[row][col]->getColour() == "white") {
        oppositeColour = "black";
    }

    // upright
    int startRow = row + 1;
    int startCol = col + 1;
    while (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
            break;
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } else {
            break;
        }
        startRow += 1;
        startCol += 1;
    }

    // upleft
    startRow = row + 1;
    startCol = col - 1;
    while (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
            break;
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } else {
            break;
        }
        startRow += 1;
        startCol -= 1;
    }

    // downright
    startRow = row - 1;
    startCol = col + 1;
    while (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
            break;
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } else {
            break;
        }
        startRow -= 1;
        startCol += 1;
    }

    // downleft
    startRow = row - 1;
    startCol = col - 1;
    while (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
            break;
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } else {
            break;
        }
        startRow -= 1;
        startCol -= 1;
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
