#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include <string>

class Pawn: public Piece {
public:
    Pawn(int row, int col, std::string piece, std::string colour, char symbol);
    virtual ~Pawn() = 0;
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override; 
};


#endif
