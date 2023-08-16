#ifndef MEDIUM_H
#define MEDIUM_H

#include "computer.h"
#include <string>
#include <memory>

class Chess;

class Medium: public Computer{
public:
    Medium(std::shared_ptr<Chess> game, std::string colour, std::string name);
    ~Medium();
    bool move();
};

#endif
