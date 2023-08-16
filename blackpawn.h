#ifndef BLACKPAWN_H
#define BLACKPAWN_H
#include "pawn.h"
#include <string>

class BlackPawn: public Pawn {
public:
    BlackPawn(int row, int col, std::string piece, std::string colour, char symbol);
    ~BlackPawn();
    void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col);
};


#endif
