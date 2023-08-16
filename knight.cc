#include "knight.h"
#include <string>

Knight::Knight(int row, int col, std::string type, std::string colour, char symbol):
    Piece{row, col, "knight", colour, symbol} {}
Knight::~Knight() {}

void Knight::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();
    std::string oppositeColour;
    if (board[row][col]->getColour() == "black") {
        oppositeColour = "white";
    } else if (board[row][col]->getColour() == "white") {
        oppositeColour = "black";
    }

    int startRow = row + 2;
    int startCol = col - 1;
    if (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    } 

    startCol = col + 1;
    if (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    } 

    startRow = row + 1;
    startCol = col + 2;
    if (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

    startRow = row - 1;
    if (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

    startRow = row - 2;
    startCol = col + 1;
    if (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

    startCol = col - 1;
    if (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

    startRow = row - 1;
    startCol = col - 2;
    if (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

    startRow = row + 1;
    if (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == oppositeColour) {
            setMoves(move{startRow, startCol, true});
        } else if (board[startRow][startCol]->getColour() == "none") {
            setMoves(move{startRow, startCol, false});
        } 
    }

}
