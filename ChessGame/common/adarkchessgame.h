#ifndef ADARKCHESSGAME_H
#define ADARKCHESSGAME_H

#include "achessgame.h"
#include "vector"

//using std::vector;

class ADarkChessGame:public AChessGame{
public:
    virtual vector<Tile> getHiddenTiles(Player player)=0;

    virtual vector<TiledPiece> getConvertionPieces(Player player);
    virtual vector<Tile> getMoveTiles(TiledPiece piece);
    virtual vector<Tile> getAttackTiles(TiledPiece piece);
    virtual Piece getPieceAtTile(Tile tile);
    virtual ChessColor getOrderPlayer();
};

#endif // ADARKCHESSGAME_H
