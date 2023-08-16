#include "bishop.h"
#include <string>
#include <iostream>

Bishop::Bishop(int row, int col, std::string piece, std::string colour, char symbol):
    Piece{row, col, "bishop", colour, symbol} {

}
Bishop::~Bishop() {}

void Bishop::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
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
}
