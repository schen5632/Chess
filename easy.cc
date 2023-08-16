#include "easy.h"
#include "chess.h"
#include <string>
#include <memory>

Easy::Easy(std::shared_ptr<Chess> game, std::string colour, std::string name): 
    Computer{game, colour, name} {}

Easy::~Easy() {}

bool Easy::move(){
    std::vector<Chess::PossibleMove> movelist = chess->allMoves();
    int r = rand_number(0, movelist.size() - 1);
    Chess::PossibleMove m = movelist.at(r);
    if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
        return true;
    }
    else return false;
}


