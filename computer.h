#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include <memory>
#include <string>

class Computer: public Player{
protected:
    // generates random number in given range
    int rand_number(int low, int high);   
public:
    // Constructor/Destructor
    Computer(std::shared_ptr<Chess> game, std::string colour, std::string name);
    virtual ~Computer() = 0;
};

#endif
