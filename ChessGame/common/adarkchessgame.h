#ifndef ADARKCHESSGAME_H
#define ADARKCHESSGAME_H

#include "achessgame.h"
#include "vector"

//using std::vector;

class ADarkChessGame:public AChessGame{
public:
    virtual vector<Tile> getHiddenTiles(Player player)=0; // FIXME(1): убрать объявление

};

#endif // ADARKCHESSGAME_H
