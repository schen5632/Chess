#ifndef GRAPHICVIEWER_H
#define GRAPHICVIEWER_H

#include <string>
#include "viewer.h"
#include <memory>
#include <vector>

class Xwindow;
class Board;

class GraphicViewer: public Viewer{
    int width;
    int height;
    int boardLeft;
    int boardRight;
    int boardTop;
    int boardBottom;

    // Display
    std::shared_ptr<Xwindow> d;

    // Chessboard
    std::shared_ptr<Chess> board;

    // 2D vector containing pieces currently displayed
    std::vector<std::vector<char>> displayed;

    // Displays board
    void displayBoard();

    // Updates board
    void updateBoard();

    // Draws Piece at coordinates
    void drawPiece(int i, int j, char c);
public:
    // Constructor/Destructor
    GraphicViewer(std::shared_ptr<Chess> board);
    GraphicViewer(int width, int height, int boardLeft, int boardRight, 
        int boardTop, int boardBottom, std::shared_ptr<Chess> board);
    ~GraphicViewer();
    void display() override;
    void update() override;
    void updateChess(std::shared_ptr<Chess> newchess) override;
    void displayMessage(std::string message) override;
};

#endif
