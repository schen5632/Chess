#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <string>

class Chess;

class Viewer{
public:
    virtual ~Viewer();
    virtual void display() = 0;
    virtual void update() = 0;
    virtual void displayMessage(std::string message) = 0;
    virtual void updateChess(std::shared_ptr<Chess> newchess) = 0;
};    

#endif
