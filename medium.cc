#include "medium.h"
#include <string>
#include <memory>
#include <iostream>
#include "chess.h"

// Constructor
Medium::Medium(std::shared_ptr<Chess> game, std::string colour, std::string name):
    Computer{game, colour, name} {}

// Destructor
Medium::~Medium() {}

bool Medium::move(){
    std::vector<Chess::PossibleMove> movelist = chess->allMoves();
    std::vector<Chess::PossibleMove> checks_captures;
    std::vector<Chess::PossibleMove> othermoves;
    for (auto m: movelist){
        if (m.capture || m.check){
            checks_captures.emplace_back(m);
        }
        else othermoves.emplace_back(m);
    }
    // If there exists checks/captures:
    if (!(checks_captures.empty())){
        int r = rand_number(0, checks_captures.size() -1);
        Chess::PossibleMove m = checks_captures.at(r);
        std::cout << "Move: " << std::endl;
        std::cout << "Orig: " << m.move.orig_x << m.move.orig_y << std::endl;
        std::cout << "Target: " << m.move.target_x << m.move.target_y << std::endl;
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        else return false;
    }
    // Otherwise:
    else{
        int r = rand_number(0, othermoves.size() - 1); 
        Chess::PossibleMove m = othermoves.at(r);
        std::cout << "Move: " << std::endl;
        std::cout << "Orig: " << m.move.orig_x << m.move.orig_y << std::endl;
        std::cout << "Target: " << m.move.target_x << m.move.target_y << std::endl;
        if (chess->makeMove(m.move.orig_x, m.move.orig_y, m.move.target_x, m.move.target_y, colour, m.promote)){
            return true;
        }
        else return false;
    }
}

