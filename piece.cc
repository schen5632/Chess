#include <string>
#include <map>
#include "piece.h"
#include <iostream>

Piece::Piece(int row, int col, std::string type, std::string colour, char symbol):
    row{row}, col{col}, type{type}, colour{colour}, symbol{symbol} {}

Piece::Piece(){ 
    symbol = ' ';
    colour = "none"; 
}

Piece::~Piece() {}

int Piece::getRow() { return row; }
int Piece::getCol() { return col; }

char Piece::getSymbol(){
    return symbol;
}

std::string Piece::getType(){
    return type;
}

std::string Piece::getColour(){
    return colour;
}

int Piece::getCount() {
    return moveCount;
}

void Piece::addCount() {
    moveCount += 1;
}

void Piece::subCount(){
    moveCount -=1;
}

void Piece::setMoves(move move) {
    moves.push_back(move);
}

std::vector<move> Piece::getMoves() {
    return moves;
}

void Piece::emptyMoves() {
    moves.clear();
}

void Piece::printMoves(std::string s) {
    std::map<int, char> col = {
        {0, 'a'},
        {1, 'b'},
        {2, 'c'},
        {3, 'd'},
        {4, 'e'},
        {5, 'f'},
        {6, 'g'},
        {7, 'h'}
    };

    std::map<int, char> row = {
        {0, '1'},
        {1, '2'},
        {2, '3'},
        {3, '4'},
        {4, '5'},
        {5, '6'},
        {6, '7'},
        {7, '8'}
    };

    std::cout << "Possible moves for " << s << getType() << ":" << std::endl;
    for(auto i: getMoves()) {      
        std::cout << col[i.col] << row[i.row] << std::endl;
    }


}

// always false; only possibly true if piece is king
bool Piece::inCheck(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col){
    throw std::out_of_range("In Checking non-king");
    return true;
 }

