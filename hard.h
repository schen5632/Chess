#ifndef HARD_H
#define HARD_H

#include "computer.h"
#include <string>
#include <memory>

class Chess;

class Hard: public Computer{
public:
    Hard(std::shared_ptr<Chess> game, std::string colour, std::string name);
    ~Hard();
    bool move();
};

#endif
