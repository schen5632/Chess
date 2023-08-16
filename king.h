#ifndef KING_H
#define KING_H
#include "piece.h"
#include <string>
#include <vector>
#include <memory>

class King: public Piece {
public:
    King(int row, int col, std::string piece, std::string colour, char symbol);
    ~King();
    bool inCheck(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col);
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) override;
    void moveKing(std::vector<std::vector<std::shared_ptr<Piece>>>& board, int orig_x, int orig_y, int target_x, int target_y);
};


#endif
