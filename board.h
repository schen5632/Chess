#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <string>

class Piece;
class Chess;

class Board{
    int king_x;
    int king_y;
    std::vector<std::vector<std::shared_ptr<Piece>>> board; 
public:
    Board();
    ~Board();
    std::shared_ptr<Piece> getPiece(int x, int y);
    void newPiece(char piece, int x, int y);
    void removePiece(int x, int y);
    void placePiece(std::shared_ptr<Piece> piece, int x, int y);
    // Places piece at coordinates
    void movePiece(int orig_x, int orig_y, int target_x, int target_y);
    // Updates movelist of all pieces
    void updatePieces();
    // Retreives board
    std::vector<std::vector<std::shared_ptr<Piece>>> getBoard();
    bool verify();
};
#endif
