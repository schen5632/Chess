#ifndef CHESSTEMP_H
#define CHESSTEMP_H

class Board{
public:
    Board();
    ~Board();
    char getTurn();
    int getState(int x, int y);
};
         
#endif
