#ifndef WHITEPAWN_H
#define WHITEPAWN_H
#include "pawn.h"
#include <string>

class WhitePawn: public Pawn {
public:
    WhitePawn(int row, int col, std::string piece, std::string colour, char symbol);
    ~WhitePawn();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col);
};


#endif
