#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

class Chess;

class Player{
protected:
    // Chess Game
    std::shared_ptr<Chess> chess;
    // colour of pieces
    std::string colour;
    // Name of player
    std::string name;
    // # of wins
    int wins = 0;
    // # of draws
    int draws = 0;
public:
    // Constructor/Destructor
    Player(std::shared_ptr<Chess> game, std::string colour, std::string name);
    virtual ~Player();

    // Player makes a move
    // Returns false if unsuccesful
    virtual bool move() = 0;
    
    void addWin();
    void addDraw();
    float getScore();
    std::string getColour();
    void changeColour(std::string c);
    std::string getName();

    void updateGame(std::shared_ptr<Chess> newchess);
};

#endif
