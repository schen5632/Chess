#include "player.h"
#include "human.h"
#include "chess.h"
#include <string>
#include <iostream>
#include <memory>
#include <map>

Human::Human(std::shared_ptr<Chess> chess, std::string colour, std::string name):
    Player{chess, colour, name} {}

Human::~Human() {}


bool Human::move(){
    std::string orig, target;
    std::map<char, int> col = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7}
    };

     std::map<char, int> row = {
        {'1', 0},
        {'2', 1},
        {'3', 2},
        {'4', 3},
        {'5', 4},
        {'6', 5},
        {'7', 6},
        {'8', 7}
    };
    
    std::cin >> orig;
    std::cin >> target;
    int orig_x = col[orig[0]];
    int orig_y = row[orig[1]];
    int target_x = col[target[0]];
    int target_y = row[target[1]];
    if (chess->makeMove(orig_x, orig_y, target_x, target_y, colour, ' ')){
        return true;
    }
    else return false;
}
        
    
    
