#ifndef EASY_H
#define EASY_H

#include "computer.h"
#include <memory>
#include <string>

class Easy: public Computer{
public:
    // Constructor/Destructor
    Easy(std::shared_ptr<Chess> game, std::string colour, std::string name);
    ~Easy();
    bool move() override;
};
    
#endif   
