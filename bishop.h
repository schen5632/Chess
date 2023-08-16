#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include <string>

class Bishop: public Piece {
public:
    Bishop(int row, int col, std::string piece, std::string colour, char symbol);
    ~Bishop();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
};


#endif
