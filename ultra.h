#ifndef ULTRA_H
#define ULTRA_H

#include "computer.h"
#include <string>
#include <memory>

class Chess;

class Ultra: public Computer{
public:
    Ultra(std::shared_ptr<Chess> game, std::string colour, std::string name);
    ~Ultra();
    bool move();
};

#endif
