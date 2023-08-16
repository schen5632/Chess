#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
#include <string>

class Queen: public Piece {
public:
    Queen(int row, int col, std::string piece, std::string colour, char symbol);
    ~Queen();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
};


#endif