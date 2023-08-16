#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include <memory>
#include <string>

class Human: public Player{
public:
    // Constructor/Destructor
    Human(std::shared_ptr<Chess> chess, std::string colour, std::string name);
    ~Human();
    bool move();
};    

#endif
