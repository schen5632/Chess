#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include <string>

class Knight: public Piece {
public:
    Knight(int row, int col, std::string piece, std::string colour, char symbol);
    ~Knight();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
};


#endif
