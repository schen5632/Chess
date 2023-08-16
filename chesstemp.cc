#include <string>
#include <iostream>
#include "chesstemp.h"

Board::Board() {}

Board::~Board() {}

char Board::getTurn(){
    char c;
    std::cout << "Turn: ";
    std::cin >> c;
    return c;
}

int Board::getState(int x, int y){
    return ((x + 1) * (y + 1)) % 10;
}
