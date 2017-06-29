#ifndef ICHESSBOARDVIEW_H
#define ICHESSBOARDVIEW_H

#include "chesscolor.h"
#include "piece.h"
#include "tile.h"
#include "ichessobserver.h"
#include "adarkchessgame.h"

class IChessBoardView:public IChessObserver{
public:
    virtual void setChessGameModel(ADarkChessGame* game=0)=0;
    virtual ADarkChessGame* getChessGameModel()=0;

    virtual void setActivePlayer(ChessColor player)=0;
    virtual ChessColor getActivePlayer()=0;
public:
signals:
    virtual void pieceMovedByPlayer(ChessColor player,Piece piece,Tile from,Tile to)=0;
    virtual void piecePromotedByPlayer(ChessColor player,TiledPiece from,TiledPiece to)=0;

};

Q_DECLARE_INTERFACE(IChessBoardView, "IChessBoardView")

#endif // ICHESSBOARDVIEW_H
