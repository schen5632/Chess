#include <iostream>
#include <memory>
#include "chess.h"
#include "textviewer.h"

// Constructor
TextViewer::TextViewer(int x, int y, std::shared_ptr<Chess> board): x{x}, y{y}, board{board} {}

// Destructor
TextViewer::~TextViewer() {}

// Displays board
void TextViewer::display(){
    whiteDisplay();
    //if (board->getTurn() == "white") whiteDisplay();
    //else blackDisplay();
} 

// Updates board; same as display 
void TextViewer::update(){
    display();
}

void TextViewer::whiteDisplay(){
    for(int i = y - 1; i >= 0; --i){
        std::cout << "  +-+-+-+-+-+-+-+-+" << std::endl;
        std::cout <<  i + 1 << " |";
        for (int j = 0; j < x; ++j){
            std::cout << getSymbol(j, i) << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "  +-+-+-+-+-+-+-+-+" << std::endl;
    std::cout << "   ";
    for (char c = 'a'; c <= 'h'; ++c){
        std::cout << c << " ";
    }   
    std::cout << std::endl;
}
            
void TextViewer::blackDisplay(){    
    for(int i = 0; i < y ; ++i){
        std::cout << "  +-+-+-+-+-+-+-+-+" << std::endl;
        std::cout << i + 1 << " |";
        for (int j = y - 1; j >= 0; --j){
            std::cout << getSymbol(j, i) << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "  +-+-+-+-+-+-+-+-+" << std::endl;
    std::cout << "   ";
    for (char c = 'h'; c >= 'a'; --c){
        std::cout << c << " ";
    }   
    std::cout << std::endl;
}

// Turns symbol int char to be displayed
char TextViewer::getSymbol(int x, int y){
    char c = board->getState(x, y);
    /*
    if (c == ' '){
        if ((x + y) % 2){
            return '_';
        }
    }
    */
    return c;
}
 
void TextViewer::displayMessage(std::string message){
    std::cout << message << std::endl;
}

void TextViewer::updateChess(std::shared_ptr<Chess> newchess){
    board = newchess;
}
