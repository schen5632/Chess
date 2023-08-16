#define BOARDWIDTH 8
#define BOARDHEIGHT 8

#include "graphicviewer.h"
#include "chess.h"
#include "window.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>

// Constructor
GraphicViewer::GraphicViewer(int width, int height, int boardLeft, 
    int boardRight, int boardTop, int boardBottom, std::shared_ptr<Chess> board):
    width{width}, height{height}, boardLeft{boardLeft},
    boardRight{boardRight}, boardTop{boardTop},
    boardBottom{boardBottom}, d{std::make_shared<Xwindow>(width, height)},
    board{board}, 
    displayed{std::vector<std::vector<char>> (8, std::vector<char>(8, ' '))} {}

// Default Constructor
GraphicViewer::GraphicViewer(std::shared_ptr<Chess> board):
    width{1000}, height{1000}, boardLeft{140}, boardRight{860},
    boardTop{100}, boardBottom{820}, d{new Xwindow(1000, 1000)},
    board{board},
    displayed{std::vector<std::vector<char>> (8, std::vector<char>(8, ' '))} {}

// Destructor
GraphicViewer::~GraphicViewer() {}

// Displays board
void GraphicViewer::displayBoard(){
    int squareWidth = (boardRight - boardLeft) / (BOARDWIDTH + 1);
    int squareHeight = (boardBottom - boardTop) / (BOARDHEIGHT + 1);
    for(int i = 0; i < BOARDHEIGHT ; ++i){
        d->drawString(boardLeft + (squareWidth / 2),
                      boardTop + (squareHeight / 2) + (squareHeight * i),
                      /* column */std::string(1, '8' - i));           
        for(int j = 0; j < BOARDWIDTH; ++j){
            d->fillRectangle(boardLeft + (squareWidth * (j + 1)),
                             boardTop + (squareHeight * i),
                             squareWidth, squareHeight,/* colour */  ((i + j) % 2)?0:2);
            drawPiece(i, j, board->getState(j, 7 - i));
            
        }
    }
    for (int i = 0; i < BOARDWIDTH; ++i){
        d->drawString(boardLeft + (squareWidth / 2) + (squareWidth *(i + 1)),
                   boardBottom - (squareHeight / 2), /* row */std::string(1, 'a' + i));
    }
}

// Updates board only where needed
void GraphicViewer::updateBoard(){
    for (int i = 0; i < BOARDHEIGHT; ++i){
        for (int j = 0; j < BOARDWIDTH; ++j){
            drawPiece(i, j, board->getState(j, 7 - i));
        }
    }
}

// Prints display in full
void GraphicViewer::display(){
    displayBoard();
}

// Updates display
void GraphicViewer::update() { 
    updateBoard();
}  

// Displays Message
void GraphicViewer::displayMessage(std::string message){
    d->drawString(500, 900, message);
}
   
void GraphicViewer::updateChess(std::shared_ptr<Chess> newchess){
    board = newchess;
}

void GraphicViewer::drawPiece(int i, int j, char c){
    int squareWidth = (boardRight - boardLeft) / (BOARDWIDTH + 1);
    int squareHeight = (boardBottom - boardTop) / (BOARDHEIGHT + 1);
    if (c != displayed.at(i).at(j)){
        d->fillRectangle(boardLeft + (squareWidth * (j + 1)),
                         boardTop + (squareHeight * i),
                         squareWidth, squareHeight,/* colour */  ((i + j) % 2)?0:2);
        d->drawString(boardLeft + (squareWidth / 2) + (squareWidth * (j + 1)),
            boardTop + (squareHeight / 2) + (squareHeight * i), /* piece */std::string(1, c));
        displayed.at(i).at(j) = c;
    }
    else return;
}
