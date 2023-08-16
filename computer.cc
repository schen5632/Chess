#include "computer.h"
#include <random>

Computer::Computer(std::shared_ptr<Chess> game, std::string colour, std::string name):
    Player{game, colour, name} {}

Computer::~Computer() {}

int Computer::rand_number(int low, int high){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(low, high);
    return distrib(gen);
}


    
