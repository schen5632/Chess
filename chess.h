#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include <memory>
class Viewer;
class Board;
class Piece;

class Chess{
public:
    struct MadeMove{
        int orig_x, orig_y, target_x, target_y;
        std::shared_ptr<Piece> moved;
        std::shared_ptr<Piece> captured;
    };
    struct PossibleMove{
        MadeMove move;
        bool capture;
        bool check;
        char promote;
    };
private:
    std::string turn = "white";
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Viewer>> viewers;
    std::vector<MadeMove> mademoves;
    int wking_x = -1, wking_y = -1, bking_x = -1, bking_y = -1;
    
    // Increments turn
    void nextTurn();

    // Moves a piece
    void move(int orig_x, int orig_y, int target_x, int target_y);
    
    // Checks if some move is valid; doesn't actually make move
    // Returns true if succesful, false otherwise
    bool tryMove(int orig_x, int orig_y, int target_x, int target_y, std::string colour);
    
    // Castle
    void castle(int target_x, int target_y);
   
    // En Passant
    bool enpassant(int orig_x, int orig_y, int target_x, int target_y);
    
    // Pawn Promotion
    void promote(int target_x, int target_y, char piece);

     // Undos move without changing turns, printing board
    void undo();

    // Updates possible moves for all pieces
    void updatePieces(); 

public:       
    // Default Constructor: creates empty board
    Chess();
    // Destructor
    ~Chess();
    
    Chess operator=(const Chess& other) = delete;
    
    // Sets up Chessboard through user input
    void userSetup();
    // Default Chess setup
    void defaultSetup();
    
    char getState(int x, int y);
    void addViewers(std::shared_ptr<Viewer> viewer);
    void removeAllViewers();
    void displayViewers();
    void updateViewers();   
    bool checkmate();
    bool stalemate();
    void getPrint(std::string s, int x, int y);

    // Returns turn of player
    std::string getTurn();
    
    // Makes Move, increments turn (May fail, would then return false)
    bool makeMove(int orig_x, int orig_y, int target_x, int target_y, std::string colour, char p);

    // Undos move
    void undoMove();  

    // Checks if current turn is in check
    bool inCheck();

    // Returns list of last moves
    std::vector<MadeMove> &getMoveList();

    // Returns a list of all possible moves
    std::vector<PossibleMove> allMoves();
};

#endif
