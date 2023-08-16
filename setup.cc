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

void placePiece(vector<vector<shared_ptr<Piece>>>& board, string piece, char x, char y) {
    if (piece == "K") {
        board[y][x] = make_shared<King>(y, x, "p", "white", piece);
    } else if (piece == "Q") {
        board[y][x] = make_shared<Queen>(y, x, "p", "white", piece);
    } else if (piece == "R") {
        board[y][x] = make_shared<Rook>(y, x, "p", "white", piece);
    } else if (piece == "B") {
        board[y][x] = make_shared<Bishop>(y, x, "p", "white", piece);
    } else if (piece == "N") {
        board[y][x] = make_shared<Knight>(y, x, "p", "white", piece);
    } else if (piece == "P") {
        board[y][x] = make_shared<WhitePawn>(y, x, "p", "white", piece);
    } else if (piece == "k") {
        board[y][x] = make_shared<King>(y, x, "p", "black", piece);
    } else if (piece == "q") {
        board[y][x] = make_shared<Queen>(y, x, "p", "black", piece);
    } else if (piece == "r") {
        board[y][x] = make_shared<Rook>(y, x, "p", "black", piece);
    } else if (piece == "b") {
        board[y][x] = make_shared<Bishop>(y, x, "p", "black", piece);
    } else if (piece == "n") {
        board[y][x] = make_shared<Knight>(y, x, "p", "black", piece);
    } else if (piece == "p") {
        board[y][x] = make_shared<BlackPawn>(y, x, "p", "black", piece);
    }
}

bool verify(vector<vector<shared_ptr<Piece>>>& board) {
    int whiteKings = 0;
    int blackKings = 0;
    bool inCheck;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7) {
                if (board[i][j]->getSymbol() == 'P' || board[i][j]->getSymbol() == 'p') {
                    cout << "No pawns are allowed in the first or last row of the board." << endl;
                    return false;
                }
            }

            if (board[i][j]->getSymbol() == 'K') {
                whiteKings++;
            } else if (board[i][j]->getSymbol() == 'k') {
                blackKings++;
                // check if black king is in check
            }


        }
    }

    if (whiteKings != 1 || blackKings != 1) {
        cout << "There must be exactly one white king and one black king." << endl;
        return false;
    }

    return true;
}

void setup(vector<vector<shared_ptr<Piece>>>& board) {
    string command;
    bool validBoard = false;

    map<char, int> col = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7}
    };

     map<int, int> row = {
        {1, 7},
        {2, 6},
        {3, 5},
        {4, 4},
        {5, 3},
        {6, 2},
        {7, 1},
        {8, 0}
    };

    while(validBoard == false) {
        getline(cin, command);
        istringstream stream(command);
        string s;
        string argOne;
        string argTwo;
        stream >> s;
        if (s == "+") {
            stream >> argOne;
            stream >> argTwo;
            char x = col[argTwo[0]];
            char y = row[argTwo[1]];
            placePiece(board, argOne, x, y);
        } else if (s == "-") {
            stream >> argOne;
            char x = col[argOne[0]];
            char y = row[argOne[1]];
            board[y][x] = make_shared<Empty>();
        } else if (s == "=") {
            stream >> argOne;
            // do colour
        } else if (s == "done") {
            // stop

        }
    }
}