#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
#include <string>

class Rook: public Piece {
public:
    Rook(int row, int col, std::string piece, std::string colour, char symbol);
    ~Rook();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
};


#endif