#include "player.h"
#include <string>

// Constructor
Player::Player(std::shared_ptr<Chess> game, std::string colour, std::string name): 
    chess{game}, colour{colour}, name{name} {}

// Destructor
Player::~Player() {}

void Player::addWin(){
    ++wins;
}

void Player::addDraw(){
    ++draws;
}

std::string Player::getColour(){
    return colour;
}

void Player::changeColour(std::string c){
    colour = c;
}

std::string Player::getName(){
    return name;
}

float Player::getScore(){
    return wins + draws / 2;
}

void Player::updateGame(std::shared_ptr<Chess> newchess){
    chess = newchess;
}
