#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H
#include <memory>
#include <string>
#include "viewer.h"
class Chess;

class TextViewer: public Viewer{
    // Size of Board
    int x, y;
    // ChessBoard
    std::shared_ptr<Chess> board;

    // Converts piece into printable piece character
    char getSymbol(int x, int y);
    // Displays board in white's perspective
    void whiteDisplay();
    // Displays board in black's perspective
    void blackDisplay();
public:
    // Constructor/Destructor
    TextViewer(int x, int y, std::shared_ptr<Chess> board);
    ~TextViewer();

    // Displays board
    void display() override;
    // Updates board
    // In this case, same as display board
    void update() override;
    // Prints text
    void displayMessage(std::string message) override;    
    // Updates Chessboard, when new game starts
    void updateChess(std::shared_ptr<Chess> newchess) override;
};

#endif
