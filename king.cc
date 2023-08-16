#include "king.h"
#include "empty.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

King::King(int row, int col, std::string piece, std::string colour, char symbol):
    Piece{row, col, "king", colour, symbol} {

}
King::~King() {}

// Returns true if king is NOT in check and false if king is in check
bool King::inCheck(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    std::string kingColour = getColour();
    std::string colour;
    int startRow;
    int startCol;

    if (kingColour == "black") {
        colour = "white";
    } else if (kingColour == "white") {
        colour = "black";
    }
	
    // Searching for checks along the same row
    for (int i = col+1; i < 8; ++i) {
        if (board[row][i]->getColour() == colour) {
            if (board[row][i]->getType() == "rook" || board[row][i]->getType() == "queen") {
                //std::cout << "A king is in check by a piece in the same row." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[row][i]->getColour() == kingColour) {
            break;
        }
    }

    for (int i = col-1; i > -1; --i) {
        if (board[row][i]->getColour() == colour) {
            if (board[row][i]->getType() == "rook" || board[row][i]->getType() == "queen") {
                //std::cout << "A king is in check by a piece in the same row." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[row][i]->getColour() == kingColour) {
            break;
        }
    }

    // Searching for checks along the same column
    for (int i = row+1; i < 8; ++i) {
        if (board[i][col]->getColour() == colour) { 
            if (board[i][col]->getType() == "rook" || board[i][col]->getType() == "queen") {
                //std::cout << "A king is in check by a piece in the same row." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[i][col]->getColour() == kingColour) {
            break;
        }
    }     

    for (int i = row-1; i > -1; --i) {
        if (board[i][col]->getColour() == colour) { 
            if (board[i][col]->getType() == "rook" || board[i][col]->getType() == "queen") {
                //std::cout << "A king is in check by a piece in the same row." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[i][col]->getColour() == kingColour) {
            break;
        }
    }   

    // Searching for checks in the diagonals

    // upright
    startRow = row + 1;
    startCol = col + 1;
    while (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour) {
            if (board[startRow][startCol]->getType() == "bishop" || board[startRow][startCol]->getType() == "queen") {
                //std::cout << "A king is in check by a piece on a diagonal." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[startRow][startCol]->getColour() == kingColour) {
            break;
        }
        startRow += 1;
        startCol += 1;
    }

    // upleft
    startRow = row + 1;
    startCol = col - 1;
    while (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour) {
            if (board[startRow][startCol]->getType() == "bishop" || board[startRow][startCol]->getType() == "queen") {
                //std::cout << "A king is in check by a piece on a diagonal." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[startRow][startCol]->getColour() == kingColour) {
            break;
        }
        startRow += 1;
        startCol -= 1;
    }

    // downright
    startRow = row - 1;
    startCol = col + 1;
    while (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour) {
            if (board[startRow][startCol]->getType() == "bishop" || board[startRow][startCol]->getType() == "queen") {
                //std::cout << "A king is in check by a piece on a diagonal." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[startRow][startCol]->getColour() == kingColour) {
            break;
        }
        startRow -= 1;
        startCol += 1;
    }

    // downleft
    startRow = row - 1;
    startCol = col - 1;
    while (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour) {
            if (board[startRow][startCol]->getType() == "bishop" || board[startRow][startCol]->getType() == "queen") {
                //std::cout << "A king is in check by a piece on a diagonal." << std::endl;
                return false;
            } else {
                break;
            }
        } else if (board[startRow][startCol]->getColour() == kingColour) {
            break;
        }
        startRow -= 1;
        startCol -= 1;
    }

    // Searching for checks by knights
    startRow = row + 2;
    startCol = col - 1;
    if (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    } 

    startCol = col + 1;
    if (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    } 

    startRow = row + 1;
    startCol = col + 2;
    if (startRow < 8 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }

    startRow = row - 1;
    if (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }

    startRow = row - 2;
    startCol = col + 1;
    if (startRow > -1 && startCol < 8) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }

    startCol = col - 1;
    if (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }

    startRow = row - 1;
    startCol = col - 2;
    if (startRow > -1 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }

    startRow = row + 1;
    if (startRow < 8 && startCol > -1) {
        if (board[startRow][startCol]->getColour() == colour && board[startRow][startCol]->getType() == "knight") {
            //std::cout << "A king is in check by a knight. " << std::endl;
            return false;
        }
    }
    // Searching for pawn checks
    if (kingColour == "white" && (row+1 < 8) && (col-1 > -1) && board[row+1][col-1]->getColour() == "black"
        && board[row+1][col-1]->getType() == "pawn") {
        //std::cout << "The white king is in check by a pawn." << std::endl;
        return false;
    } else if (kingColour == "white" && (row+1 < 8) && (col+1 < 8) && board[row+1][col+1]->getColour() == "black"
        && board[row+1][col+1]->getType() == "pawn") {
        //std::cout << "The white king is in check by a pawn." << std::endl;
        return false;
    } else if (kingColour == "black" && (row-1 > -1) && (col-1 > -1) && board[row-1][col-1]->getColour() == "white"
        && board[row-1][col-1]->getType() == "pawn") {
        //std::cout << "The black king is in check by a pawn." << std::endl;
        return false;
    } else if (kingColour == "black" && (row-1 > -1) && (col+1 < 8) && board[row-1][col+1]->getColour() == "white"
        && board[row-1][col+1]->getType() == "pawn") {
        //std::cout << "The black king is in check by a pawn." << std::endl;
        return false;
    } 

    // Searching for king checks
    if ((row+1 < 8 && board[row+1][col]->getColour() == colour && board[row+1][col]->getType() == "king") ||
        ((row+1 < 8 && col+1 < 8) && board[row+1][col+1]->getColour() == colour && board[row+1][col+1]->getType() == "king") ||
        (col+1 < 8 && board[row][col+1]->getColour() == colour && board[row][col+1]->getType() == "king") ||
        ((row-1 > -1 && col+1 < 8) && board[row-1][col+1]->getColour() == colour && board[row-1][col+1]->getType() == "king") || 
        (row-1 > -1 && board[row-1][col]->getColour() == colour && board[row-1][col]->getType() == "king") ||
        ((row-1 > -1 && col-1 > -1) && board[row-1][col-1]->getColour() == colour && board[row-1][col-1]->getType() == "king") || 
        (col-1 > -1 && board[row][col-1]->getColour() == colour && board[row][col-1]->getType() == "king") ||
        ((row+1 < 8 && col-1 > -1) && board[row+1][col-1]->getColour() == colour && board[row+1][col-1]->getType() == "king")) {
        //std::cout << "The kings are checking each other." << std::endl;
        return false;
    }        
    return true;
}

void King::moveKing(std::vector<std::vector<std::shared_ptr<Piece>>>& board, int orig_x, int orig_y, int target_x, int target_y) {
    board.at(target_y).at(target_x) = board.at(orig_y).at(orig_x);
    board.at(orig_y).at(orig_x) = std::make_shared<Empty>();
}

void King::possibleMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board, int row, int col) {
    emptyMoves();
    std::string oppositeColour;
    if (board[row][col]->getColour() == "black") {
        oppositeColour = "white";
    } else if (board[row][col]->getColour() == "white") {
        oppositeColour = "black";
    }

    // Checking for captures
    if (row+1 < 8 && board[row+1][col]->getColour() == oppositeColour) {
        moveKing(board, col, row, col, row+1);
        if(inCheck(board, row+1, col)) {
            setMoves(move{row+1, col, true});
        }
        moveKing(board, col, row+1, col, row);
    } 
    
    if ((row+1 < 8 && col+1 < 8) && board[row+1][col+1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col+1, row+1);
        if(inCheck(board, row+1, col+1)) {
            setMoves(move{row+1, col+1, true});
        }
        moveKing(board, col+1, row+1, col, row);
    } 
    
    if (col+1 < 8 && board[row][col+1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col+1, row);
        if(inCheck(board, row, col+1)) {
            setMoves(move{row, col+1, true});
        }
        moveKing(board, col+1, row, col, row);
    } 
    
    if ((row-1 > -1 && col+1 < 8) && board[row-1][col+1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col+1, row-1);
        if(inCheck(board, row-1, col+1)) {
            setMoves(move{row-1, col+1, true});
        }
        moveKing(board, col+1, row-1, col, row);
    } 
    
    if (row-1 > -1 && board[row-1][col]->getColour() == oppositeColour) {
        moveKing(board, col, row, col, row-1);
        if(inCheck(board, row-1, col)) {
            setMoves(move{row-1, col, true});
        }
        moveKing(board, col, row-1, col, row);
    } 
    
    if ((row-1 > -1 && col-1 > -1) && board[row-1][col-1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col-1, row-1);
        if(inCheck(board, row-1, col-1)) {
            setMoves(move{row-1, col-1, true});
        }
        moveKing(board, col-1, row-1, col, row);
    } 
    
    if (col-1 > -1 && board[row][col-1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col-1, row);
        if(inCheck(board, row, col-1)) {
            setMoves(move{row, col-1, true});
        }
        moveKing(board, col-1, row, col, row);
    } 
    
    if ((row+1 < 8 && col-1 > -1) && board[row+1][col-1]->getColour() == oppositeColour) {
        moveKing(board, col, row, col-1, row+1);
        if(inCheck(board, row+1, col-1)) {
            setMoves(move{row+1, col-1, true});
        }
        moveKing(board, col-1, row+1, col, row);
    }

    // Checking for regular moves
    if (row+1 < 8 && board[row+1][col]->getColour() == "none") {
        moveKing(board, col, row, col, row+1);
        if(inCheck(board, row+1, col)) {
            setMoves(move{row+1, col, false});
        }
        moveKing(board, col, row+1, col, row); 
    } 
    
    if ((row+1 < 8 && col+1 < 8) && board[row+1][col+1]->getColour() == "none") {
        moveKing(board, col, row, col+1, row+1);
        if(inCheck(board, row+1, col+1)) {
            setMoves(move{row+1, col+1, false});
        }
        moveKing(board, col+1, row+1, col, row); 
    } 
    
    if (col+1 < 8 && board[row][col+1]->getColour() == "none") {
        moveKing(board, col, row, col+1, row);
        if(inCheck(board, row, col+1)) {
            setMoves(move{row, col+1, false});
        }
        moveKing(board, col+1, row, col, row); 
    } 
    
    if ((row-1 > -1 && col+1 < 8) && board[row-1][col+1]->getColour() == "none") {
        moveKing(board, col, row, col+1, row-1);
        if(inCheck(board, row-1, col+1)) {
            setMoves(move{row-1, col+1, false});
        }
        moveKing(board, col+1, row-1, col, row);
    } 
    
    if (row-1 > -1 && board[row-1][col]->getColour() == "none") {
        moveKing(board, col, row, col, row-1);
        if(inCheck(board, row-1, col)) {
            setMoves(move{row-1, col, false});
        }
        moveKing(board, col, row-1, col, row);
    } 
    
    if ((row-1 > -1 && col-1 > -1) && board[row-1][col-1]->getColour() == "none") {
        moveKing(board, col, row, col-1, row-1);
        if(inCheck(board, row-1, col-1)) {
            setMoves(move{row-1, col-1, false});
        }
        moveKing(board, col-1, row-1, col, row);
    } 
    
    if (col-1 > -1 && board[row][col-1]->getColour() == "none") {
        moveKing(board, col, row, col-1, row);
        if(inCheck(board, row, col-1)) {
            setMoves(move{row, col-1, false});
        }
        moveKing(board, col-1, row, col, row);
    } 
    
    if ((row+1 < 8 && col-1 > -1) && board[row+1][col-1]->getColour() == "none") {
        moveKing(board, col, row, col-1, row+1);
        if(inCheck(board, row+1, col-1)) {
            setMoves(move{row+1, col-1, false});
        }
        moveKing(board, col-1, row+1, col, row);
    }

    // Checking for white king castles
    if (row == 0 && col == 4 && board[row][col]->getColour() == "white" && board[row][col]->getCount() == 0) {
        if (board[0][0]->getType() == "rook" && board[0][0]->getCount() == 0 && board[0][0]->getColour() == "white"
            && board[row][3]->getColour() == "none" && board[row][2]->getColour() == "none" && board[row][1]->getColour() == "none") {
            moveKing(board, col, row, col-1, row);
            if(inCheck(board, row, col-1)) {
                moveKing(board, col, row, col-2, row);
                if(inCheck(board, row, col-2)) {
                    setMoves(move{row, col-2, false});
                }
                moveKing(board, col-2, row, col-1, row); 
            }
            moveKing(board, col-1, row, col, row);
        }

        if (board[0][7]->getType() == "rook" && board[0][7]->getCount() == 0 && board[0][7]->getColour() == "white"
            && board[row][col+1]->getColour() == "none" && board[row][col+2]->getColour() == "none") {
            moveKing(board, col, row, col+1, row);
            if(inCheck(board, row, col+1)) {
                moveKing(board, col, row, col+2, row);
                if(inCheck(board, row, col+2)) {
                    setMoves(move{row, col+2, false});
                }
                moveKing(board, col+2, row, col+1, row); 
            }
            moveKing(board, col+1, row, col, row);
        }
    }

    // Checking for black king castles
    if (row == 7 && col == 4 && board[row][col]->getColour() == "black" && board[row][col]->getCount() == 0) {
        if (board[7][0]->getType() == "rook" && board[7][0]->getCount() == 0 && board[7][0]->getColour() == "black"
            && board[row][3]->getColour() == "none" && board[row][2]->getColour() == "none" && board[row][1]->getColour() == "none") {
            moveKing(board, col, row, col-1, row);
            if(inCheck(board, row, col-1)) {
                moveKing(board, col, row, col-2, row);
                if(inCheck(board, row, col-2)) {
                    setMoves(move{row, col-2, false});
                }
                moveKing(board, col-2, row, col-1, row); 
            }
            moveKing(board, col-1, row, col, row);
        }

        if (board[7][7]->getType() == "rook" && board[7][7]->getCount() == 0 && board[7][7]->getColour() == "black"
            && board[row][col+1]->getColour() == "none" && board[row][col+2]->getColour() == "none") {
            moveKing(board, col, row, col+1, row);
            if(inCheck(board, row, col+1)) {
                moveKing(board, col, row, col+2, row);
                if(inCheck(board, row, col+2)) {
                    setMoves(move{row, col+2, false});
                }
                moveKing(board, col+2, row, col+1, row); 
            }
            moveKing(board, col+1, row, col, row); 
        }
    }


}
