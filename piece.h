#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>

struct move {
    int row;
    int col;
    bool capture;
    bool check = false;
};

class Piece {
private:
    int row;
    int col;
    std::string type;
    std::string colour;
    char symbol;
    int moveCount = 0;
    std::vector<move> moves;
protected:
    
public:
    char getSymbol();
    int getRow();
    int getCol();
    int getCount();
    void addCount();
    void subCount();
    std::string getType();
    std::string getColour();
    void setMoves(move move);
    std::vector<move> getMoves();
    void emptyMoves();
    void printMoves(std::string s);

    virtual bool inCheck(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col);
    
    // enter the current row of the piece in row and the current column of the piece in col
    virtual void possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) = 0; 
    Piece(int row, int col, std::string type, std::string colour, char symbol);

    // Constructor for empty piece
    Piece();
    virtual ~Piece();
};

#endif
