#ifndef ADARKCHESSGAME_H
#define ADARKCHESSGAME_H

#include "achessgame.h"
#include "types.h"
#include "vector"

using std::vector;

class ADarkChessGame:public AChessGame{
public:
    virtual vector<Tile> getHiddenTiles(Player player)=0;
};

#endif // ADARKCHESSGAME_H
