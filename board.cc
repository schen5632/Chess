#include "board.h"
#include <string>
#include <iostream>
#include <sstream>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "blackpawn.h"
#include "whitepawn.h"
#include "empty.h"
#include <vector>
#include <memory>
#include <map>

using namespace std;

Board::Board(): 
    board {vector<vector<shared_ptr<Piece>>> (8, vector<shared_ptr<Piece>> (8, make_shared<Empty>()))} {}

Board::~Board() {}

// Creates new piece, places it at location
void Board::newPiece(char piece, int x, int y) {
    if (piece == 'K') {
        board[y][x] = make_shared<King>(y, x, "p", "white", piece);
    } else if (piece == 'Q') {
        board[y][x] = make_shared<Queen>(y, x, "p", "white", piece);
    } else if (piece == 'R') {
        board[y][x] = make_shared<Rook>(y, x, "p", "white", piece);
    } else if (piece == 'B') {
        board[y][x] = make_shared<Bishop>(y, x, "p", "white", piece);
    } else if (piece == 'N') {
        board[y][x] = make_shared<Knight>(y, x, "p", "white", piece);
    } else if (piece == 'P') {
        board[y][x] = make_shared<WhitePawn>(y, x, "p", "white", piece);
    } else if (piece == 'k') {
        board[y][x] = make_shared<King>(y, x, "p", "black", piece);
    } else if (piece == 'q') {
        board[y][x] = make_shared<Queen>(y, x, "p", "black", piece);
    } else if (piece == 'r') {
        board[y][x] = make_shared<Rook>(y, x, "p", "black", piece);
    } else if (piece == 'b') {
        board[y][x] = make_shared<Bishop>(y, x, "p", "black", piece);
    } else if (piece == 'n') {
        board[y][x] = make_shared<Knight>(y, x, "p", "black", piece);
    } else if (piece == 'p') {
        board[y][x] = make_shared<BlackPawn>(y, x, "p", "black", piece);
    }
}

// Verifies whether board is correct
bool Board::verify() {
    int whiteKings = 0;
    int blackKings = 0;
    bool inCheck = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7) {
                if ((board[i][j])->getType() == "pawn") {
                    cout << "No pawns are allowed in the first or last row of the board." << endl;
                    return false;
                }
            }

            if ((board[i][j])->getSymbol() == 'K') {
                whiteKings++;
                // check if king is in check
                inCheck = board[i][j]->inCheck(board, i, j);
                if (!inCheck) {
                    cout << "White King is in Check" << endl;
                    return false;
                }
            } else if ((board[i][j])->getSymbol() == 'k') {
                blackKings++;
                // check if black king is in check
                inCheck = board[i][j]->inCheck(board, i, j);
                if (!inCheck) {
                    cout << "Black King is in Check" << endl;
                    return false;
                }
            }
        }
    }

    if (whiteKings != 1 || blackKings != 1) {
        cout << "There must be exactly one white king and one black king." << endl;
        return false;
    }

    return true;
}

// Returns piece at coords
shared_ptr<Piece> Board::getPiece(int x, int y){
    return board.at(y).at(x);
}

// Removes piece from board, replace with empty piece
void Board::removePiece(int x, int y){
    board[y][x] = make_shared<Empty>();
}

// Moves piece from orig to target
// Removes piece taken from scope
void Board::movePiece(int orig_x, int orig_y, int target_x, int target_y){
    board.at(target_y).at(target_x) = board.at(orig_y).at(orig_x);
    
    board.at(orig_y).at(orig_x) = make_shared<Empty>();
}

// Returns board
vector<vector<shared_ptr<Piece>>> Board::getBoard(){
    return board;
}

// Updates movelist of all pieces
void Board::updatePieces(){
    for (int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i){
            board.at(j).at(i)->possibleMoves(board, j, i);
        }
    }
}

// Places piece on board
void Board::placePiece(shared_ptr<Piece> piece, int x, int y){
    board.at(y).at(x) = piece;
}
