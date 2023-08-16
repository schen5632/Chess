#include "board.h"
#include "chess.h"
#include "piece.h"
#include "viewer.h"
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <sstream>
#include <cstring>
using namespace std;

Chess::Chess(): board{std::make_shared<Board>()} {}

Chess::~Chess() {}

char Chess::getState(int x, int y){
    return (board->getPiece(x, y))->getSymbol();
}

void Chess::getPrint(std::string s, int x, int y) {
    board->getPiece(x,y)->printMoves(s);
}

void Chess::displayViewers(){
    for (auto v: viewers){
        v->display();
    }
}

void Chess::updateViewers(){
    for (auto v: viewers){
        v->update();
    }
}

void Chess::addViewers(std::shared_ptr<Viewer> viewer){
    viewers.emplace_back(viewer);
}

void Chess::removeAllViewers(){
    while(!(viewers.empty())){
        viewers.pop_back();
    }
}

std::string Chess::getTurn(){
    return turn;
}

// Prompts user to setup board
void Chess::userSetup() {
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

     map<char, int> row = {
        {'1', 0},
        {'2', 1},
        {'3', 2},
        {'4', 3},
        {'5', 4},
        {'6', 5},
        {'7', 6},
        {'8', 7}
    };
    // Initially displays board
    displayViewers();
    // gets user input
    while(validBoard == false) {
        // operator
        string s;
        // piece
        char p;
        // move
        string m;
        cin >> s;
        if (s == "+") {
            cin >> p;
            cin >> m;
            int x = col[m[0]];
            int y = row[m[1]];
            board->newPiece(p, x, y);
            updateViewers();
        } else if (s == "-") {
            cin >> m;
            int x = col[m[0]];
            int y = row[m[1]];
            board->removePiece(x, y);
            updateViewers();
        } else if (s == "=") {
            if (m == "white"){
                turn = "white";
            } else if (m == "black"){
                turn = "black";
            } else cout << "invalid colour" << endl;
        } else if (s == "done") {
            validBoard = board->verify();
        } else {
            cout << "Invalid Operator" << endl;
        } // else
    } // while
    // set king positions
    for(int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i){
            if (board->getPiece(i, j)->getType() == "king"){
                if (board->getPiece(i, j)->getColour() == "white"){
                    wking_x = i;
                    wking_y = j;
                }
                else if (board->getPiece(i, j)->getColour() == "black"){
                    bking_x = i;
                    bking_y = j;
                }
            }
        }
    }
    if (wking_x == -1 || bking_x == -1 || wking_y == -1 || bking_y == -1){
        throw out_of_range("King position setting not working");
    }
    board->updatePieces();
}

void Chess::defaultSetup(){
    board->newPiece('R', 0, 0);
    board->newPiece('N', 1, 0);    
    board->newPiece('B', 2, 0);
    board->newPiece('Q', 3, 0);
    board->newPiece('K', 4, 0);
    board->newPiece('B', 5, 0);
    board->newPiece('N', 6, 0);
    board->newPiece('R', 7, 0);
    board->newPiece('P', 0, 1);
    board->newPiece('P', 1, 1);
    board->newPiece('P', 2, 1);
    board->newPiece('P', 3, 1);
    board->newPiece('P', 4, 1);
    board->newPiece('P', 5, 1);
    board->newPiece('P', 6, 1);
    board->newPiece('P', 7, 1);
    board->newPiece('p', 0, 6);
    board->newPiece('p', 1, 6);
    board->newPiece('p', 2, 6);
    board->newPiece('p', 3, 6);
    board->newPiece('p', 4, 6);
    board->newPiece('p', 5, 6);
    board->newPiece('p', 6, 6);
    board->newPiece('p', 7, 6);
    board->newPiece('r', 0, 7);
    board->newPiece('n', 1, 7);
    board->newPiece('b', 2, 7);
    board->newPiece('q', 3, 7);
    board->newPiece('k', 4, 7);
    board->newPiece('b', 5, 7);
    board->newPiece('n', 6, 7);
    board->newPiece('r', 7, 7);
    wking_x = 4;
    wking_y = 0;
    bking_x = 4;
    bking_y = 7;
    board->updatePieces();
}

// Moves a piece, Warning: does not check if move is valid
void Chess::move(int orig_x, int orig_y, int target_x, int target_y){
    // Adds move to moves list
    mademoves.emplace_back(MadeMove{orig_x, orig_y, target_x, target_y, 
        board->getPiece(orig_x, orig_y), board->getPiece(target_x, target_y)});
    // makes move
    board->movePiece(orig_x, orig_y, target_x, target_y);
    // Adds 1 to piece movecount
    board->getPiece(target_x, target_y)->addCount();
    // Update king position
    if (board->getPiece(target_x, target_y)->getType() == "king"){
        if (board->getPiece(target_x, target_y)->getColour() == "white"){
            wking_x = target_x;
            wking_y = target_y;
        }
        else if (board->getPiece(target_x, target_y)->getColour() == "black"){
            bking_x = target_x;
            bking_y = target_y;
        }
    }
}

// Checks if some move is valid, does not actually make move
bool Chess::tryMove(int orig_x, int orig_y, int target_x, int target_y, string colour){
    // Makes sure piece is right colour
    if (board->getPiece(orig_x, orig_y)->getColour() != colour){
        return false;
    }
    for (auto m: board->getPiece(orig_x, orig_y)->getMoves()){
        //std::cout << m.row << m.col << ": " << board->getPiece(orig_x, orig_y)->getSymbol() << endl;
        // If move is valid, move piece
        if ((m.row == target_y) && (m.col == target_x)){
            // move piece
            move(orig_x, orig_y, target_x, target_y);
            // If move causes check, undo move, return false
            if (inCheck()){
                undo();
                return false;
            }
            else{
                undo();
                return true;
           }
        }
    }
    // Move wasn't found
    return false;
}

bool Chess::makeMove(int orig_x, int orig_y, int target_x, int target_y, string colour, char p){
    // Castling
        // DELETE LATER
        cout << orig_x << orig_y << " " << target_x << target_y << endl;
    if ((board->getPiece(orig_x, orig_y)->getType() == "king") &&
     (((orig_x - target_x) == -2) || ((orig_x - target_x) == 2))){
        castle(target_x, target_y);
        nextTurn();
        board->updatePieces();
        return true;
    }   
    // En Passant
    else if ((board->getPiece(orig_x, orig_y)->getType() == "pawn") &&
             (target_x != orig_x) && (board->getPiece(target_x, target_y)->getColour() == "none")){
        if (enpassant(orig_x, orig_y, target_x, target_y)){
            nextTurn();
            board->updatePieces();
            return true;
        }
        else return false;
    }
        
    else if (tryMove(orig_x, orig_y, target_x, target_y, colour)){ 
        move(orig_x, orig_y, target_x, target_y);
        // Pawn Promotion
        if ((board->getPiece(target_x, target_y)->getType() == "pawn") &&
            ((target_y == 0) || (target_y == 7))){
            promote(target_x, target_y, p);
        }
        nextTurn();
        board->updatePieces();
        return true;
    }
    else{
        return false;
    }
}

// Undos previous move 
void Chess::undo(){
    bool castle_or_enpassant = false;
    if (mademoves.empty()){
        cout << "No moves have been made" << endl;
        return;
    }
    // Check for castle 
    if((mademoves.back().moved->getType() == "king") &&
      (((mademoves.back().orig_x - mademoves.back().target_x) == -2) ||
      ((mademoves.back().orig_x - mademoves.back().target_x) == 2))){
        castle_or_enpassant = true;
    }
    // Check for En Passant
    int direction;
    if (turn == "white"){
        // Undo happens to "opponent's" move, so last move is black's
        // White's pawn then goes backwards in move creation, which would be in negative direction
        direction = -1;
    }
    else if (turn == "black"){
        direction = 1;
    }
    // Checking if 2 moves ago, your own pawn moved in opposite direction
    if ((mademoves.size() >= 2) &&
        (mademoves.at(mademoves.size() - 2).moved->getType() == "pawn") &&
        (mademoves.at(mademoves.size() - 2).moved->getColour() == turn) &&
        ((mademoves.at(mademoves.size() - 2).target_y - mademoves.at(mademoves.size() - 2).orig_y) == direction)){
        castle_or_enpassant = true;
    }   
    // Update king position
    if (mademoves.back().moved->getType() == "king"){
        if (mademoves.back().moved->getColour() == "white"){
            wking_x = mademoves.back().orig_x;
            wking_y = mademoves.back().orig_y;
        }
        if (mademoves.back().moved->getColour() == "black"){
            bking_x = mademoves.back().orig_x;
            bking_y = mademoves.back().orig_y;
        }
    }   
    // reduce move count for piece moved
    mademoves.back().moved->subCount();
    // Place pieces back on board
    board->placePiece(mademoves.back().moved, mademoves.back().orig_x, mademoves.back().orig_y);
    board->placePiece(mademoves.back().captured, mademoves.back().target_x, mademoves.back().target_y);
    // Removes move from undo list
    mademoves.pop_back();
    if (castle_or_enpassant){ 
        undo();
    }     
}

// Undos previous move
void Chess::undoMove(){
    undo();
    nextTurn();
    board->updatePieces();
}

// Checks if current player is in check
bool Chess::inCheck(){
    if (turn == "white"){
        return !(board->getPiece(wking_x, wking_y)->inCheck(board->getBoard(), wking_y, wking_x));
    }
    if (turn == "black"){
        return !(board->getPiece(bking_x, bking_y)->inCheck(board->getBoard(), bking_y, bking_x));
    }
    cout << "Chess::inCheck not working" << endl;
    return false;
}

// Changes turn
void Chess::nextTurn(){
    // Increments turn
    if (turn == "white"){
        turn = "black";
    }
    else turn = "white";
}

// Returns true if king of current players turn is in checkmate
bool Chess::checkmate(){
    if (!inCheck()) return false;
    for (int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i){  
            if (board->getPiece(i, j)->getColour() == turn){ 
                for (auto m: board->getPiece(i, j)->getMoves()){
                    // False if move is able to be made
                    if(tryMove(i, j, m.col, m.row, turn)) return false;
                }
            } // if
        } // for
    } // for
    // No valid moves
    return true;
} // checkmate
            
// Returns true if current player is in stalemate
bool Chess::stalemate(){
    if (inCheck()) return false;
    for (int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i){  
            if (board->getPiece(i, j)->getColour() == turn){ 
                for (auto m: board->getPiece(i, j)->getMoves()){
                    // False if move is able to be made
                    if(tryMove(i, j, m.col, m.row, turn)) return false;
                }
            } // if
        } // for
    } // for
    // No valid moves
    return true;
}// stalemate

// Returns list of last moves
std::vector<Chess::MadeMove> &Chess::getMoveList(){
    return mademoves;
}

// Returns a list of all possible moves
std::vector<Chess::PossibleMove> Chess::allMoves(){
    vector<PossibleMove> moves;
    for (int j = 0; j < 8; ++j){
        for (int i = 0; i < 8; ++i){
            if (board->getPiece(i, j)->getColour() == turn){
                for (auto m: board->getPiece(i, j)->getMoves()){
                    if ((board->getPiece(i, j)->getType() == "pawn") && ((m.row == 7) || (m.row == 0))){
                        if (turn == "white"){
                            for (char c: vector<char>{'Q', 'R', 'B', 'N'}){
                                if (makeMove(i, j, m.col, m.row, turn, c)){
                                    bool check = false;
                                    // Makes move, then checks if opponent is in check
                                    if (inCheck()) check = true;
                                    undoMove();
                                    moves.emplace_back(PossibleMove{MadeMove{i, j, m.col, m.row, 
                                        board->getPiece(i, j), board->getPiece(m.col, m.row)}, 
                                        m.capture, check, c});
                                 }// if
                            } // for
                        } // if
                        if (turn == "black"){
                            for (char c: vector<char>{'q', 'r', 'b', 'n'}){
                                if (makeMove(i, j, m.col, m.row, turn, c)){
                                    bool check = false;
                                    // Makes move, then checks if opponent is in check
                                    if (inCheck()) check = true;
                                    undoMove();
                                    moves.emplace_back(PossibleMove{MadeMove{i, j, m.col, m.row, 
                                        board->getPiece(i, j), board->getPiece(m.col, m.row)}, 
                                        m.capture, check, c});
                                 }// if
                            } // for
                        } // if
                    } // if
                    else if (makeMove(i, j, m.col, m.row, turn, ' ')){
                        bool check = false;
                        // Makes move, then checks if opponent is in check
                        if (inCheck()) check = true;
                        undoMove();
                        moves.emplace_back(PossibleMove{MadeMove{i, j, m.col, m.row, 
                            board->getPiece(i, j), board->getPiece(m.col, m.row)}, 
                            m.capture, check, ' '});
                    }
                }
            }
        }
    }
    return moves;
}

// Performs Castle
// Note: Important that king move happens 2nd for undo to work
void Chess::castle(int target_x, int target_y){
    // White Castles
    if (target_y == 0 && turn == "white"){
        // Queenside Castle
        if (target_x == 2){
            // Rook Move
            move(0, 0, 3, 0);
            // King Move
            move(wking_x, wking_y, target_x, target_y);
        }
        // Kingside Castle
        else if (target_x == 6){
            move(7, 0, 5, 0);
            move(wking_x, wking_y, target_x, target_y);
        }
    }
    // Black Castles
    else if (target_y == 7 && turn == "black"){
        // QUeenside Castle
        if (target_x == 2){
            move(0, 7, 3, 7);
            move(bking_x, bking_y, target_x, target_y);
        }
        // Kingside Castle
        else if (target_x == 6){
            move(7, 7, 5, 7);
            move(bking_x, bking_y, target_x, target_y);
        }
    }
    // False if wrong turn
}                
           
// Performs pawn promotion
// Replaces pawn at target coordinates with piece
void Chess::promote(int target_x, int target_y, char piece){
    bool promoted = false;
    if (piece == ' '){
        char input;
        std::cin >> input;
        piece = input;
    }
    while(!promoted){
        if (turn == "white"){
            if ((piece == 'Q') || (piece == 'R') || (piece == 'N') || (piece == 'B')){
                board->newPiece(piece, target_x, target_y);
                promoted = true;
            }
        }
        else if (turn == "black"){
            if ((piece == 'q') || (piece == 'r') || (piece == 'n') || (piece == 'b')){
                board->newPiece(piece, target_x, target_y);
                promoted = true;
            }
        }
        else {
            std::cout << "Invalid Promotion Piece" << std::endl;
        }
    }
}

// Performs En Passant (moves piece)
// Returns true if successful, false otherwiuse
bool Chess::enpassant(int orig_x, int orig_y, int target_x, int target_y){
    MadeMove lastmove = mademoves.back();
    // Last moved isn't pawn
    if (lastmove.moved->getType() != "pawn") return false;
    int backpawnrow, two_up_from_pawnbackrow;
    if (turn == "white"){
        backpawnrow = 6, two_up_from_pawnbackrow = 4;
    }
    else if (turn == "black"){
        backpawnrow = 1, two_up_from_pawnbackrow = 3;
    }
    else throw out_of_range{"enpassant turn no work"};
    
    if ((lastmove.target_x == target_x) && (lastmove.target_y == two_up_from_pawnbackrow) && 
        (lastmove.orig_y == backpawnrow)){
        move(lastmove.target_x, lastmove.target_y, target_x, target_y);
        move(orig_x, orig_y, target_x, target_y);
        if (inCheck()){
            undo();
            return false;
        }
        else return true;
    }
    else return false;
}
            




