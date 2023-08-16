#ifndef EMPTY_H
#define EMPTY_H
#include "piece.h"
#include <string>

class Empty: public Piece {
public:
    Empty();
    ~Empty();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
};


#endif
