#include "ultra.h"
#include "chess.h"
#include <string>
#include <memory>

// Constructor
Ultra::Ultra(std::shared_ptr<Chess> game, std::string colour, std::string name):
    Computer{game, colour, name} {}

// Destructor
Ultra::~Ultra() {};

bool Ultra::move(){
    std::vector<Chess::PossibleMove> movelist = chess->allMoves();
    // Contains moves that avoid captures, checks, captures
    std::vector<Chess::PossibleMove> goodmoves;
    // All other moves
    std::vector<Chess::PossibleMove> badmoves;
    for (auto m: movelist){
        // Add to goodmoves 
        if (m.capture || m.check){
            goodmoves.emplace_back(m);
        }
        else if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            std::vector<Chess::PossibleMove> movelist_2 = chess->allMoves();
            for (auto q: movelist_2){
                if ((q.move.target_x == m.move.target_x) || (q.move.target_y != m.move.target_y)){
                    badmoves.emplace_back(m);
                }
                else goodmoves.emplace_back(m);
            } // for
            chess->undoMove();
        } // else if
    }

    // Finding best possible move in good moves if good moves exist
    if (!goodmoves.empty()) {
        int max = 0;
        int maxAt = 0;
        for (size_t i = 0; i < goodmoves.size(); ++i) {
            char piece = ' ';
            int pieceVal;
            Chess::PossibleMove m = goodmoves.at(i);
            if (m.capture) {
                piece = chess->getState(m.move.target_x, m.move.target_y);
            } else if (!m.capture && !m.check) {
                piece = chess->getState(m.move.orig_x, m.move.orig_y);
            }
            if (piece == 'p' || piece == 'P') {
                pieceVal = 1;
            } else if (piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N') {
                pieceVal = 3;
            } else if (piece == 'r' || piece == 'R') {
                pieceVal = 5;
            } else if (piece == 'q' || piece == 'Q') {
                pieceVal = 9;
            }

            if (max < pieceVal || (max == pieceVal && m.capture && m.check)) {
                maxAt = i;
                max = pieceVal;
            } 
        }
        Chess::PossibleMove m = goodmoves.at(maxAt);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        return false;
    } else { // no good moves
        int r = rand_number(0, badmoves.size() - 1); 
        Chess::PossibleMove m = badmoves.at(r);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        return false;
    }

    /*
    // If there exists good moves:
    if (!(goodmoves.empty())){
        int r = rand_number(0, goodmoves.size() - 1);
        Chess::PossibleMove m = goodmoves.at(r);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour)){
            return true;
        }
        else return false;
    }     
    // Otherwise:
    else{
        int r = rand_number(0, badmoves.size() - 1); 
        Chess::PossibleMove m = badmoves.at(r);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour)){
            return true;
        }
        else return false;
    } */
}
             
