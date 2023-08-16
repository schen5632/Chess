#include "pawn.h"
#include <string>

Pawn::Pawn(int row, int col, std::string piece, std::string colour, char symbol):
    Piece{row, col, "pawn", colour, symbol} {

}

Pawn::~Pawn() {}

void Pawn::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    
}
