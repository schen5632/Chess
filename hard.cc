#include "hard.h"
#include "chess.h"
#include <string>
#include <memory>

// Constructor
Hard::Hard(std::shared_ptr<Chess> game, std::string colour, std::string name):
    Computer{game, colour, name} {}

// Destructor
Hard::~Hard() {}

bool Hard::move(){
    std::vector<Chess::PossibleMove> movelist = chess->allMoves();
    // Contains moves that avoid captures, checks, captures
    std::vector<Chess::PossibleMove> goodmoves;
    // All other moves
    std::vector<Chess::PossibleMove> badmoves;
    for (auto m: movelist){
        // Add to goodmoves if move is check or capture
        if (m.capture || m.check){
            goodmoves.emplace_back(m);
        }
        // Otherwise, ***make move***, then see if opponent can capture it
        else if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            std::vector<Chess::PossibleMove> movelist_2 = chess->allMoves();
            for (auto q: movelist_2){
                if ((q.move.target_x == m.move.target_x) && (q.move.target_y == m.move.target_y)){
                    badmoves.emplace_back(m);
                    break;
                }
                else{
                    goodmoves.emplace_back(m);
                    break;
                }
            } // for
            // ***UNDOS MOVE***
            chess->undoMove();
        } // else if
    }
    // If there exists good moves:
    if (!(goodmoves.empty())){
        int r = rand_number(0, goodmoves.size() - 1);
        Chess::PossibleMove m = goodmoves.at(r);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        else return false;
    }     
    // Otherwise:
    else{
        int r = rand_number(0, badmoves.size() - 1); 
        Chess::PossibleMove m = badmoves.at(r);
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        else return false;
    }
}
             
