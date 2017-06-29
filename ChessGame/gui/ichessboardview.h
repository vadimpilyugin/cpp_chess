#ifndef ICHESSBOARDVIEW_H
#define ICHESSBOARDVIEW_H

#include "chesscolor.h"
#include "piece.h"
#include "tile.h"
#include "ichessobserver.h"
#include "adarkchessgame.h"

class IChessBoardView:public IChessObserver{
public:
    virtual ~IChessBoardView(){}
    //Установить модель для представление
    virtual void setChessGameModel(ADarkChessGame* game=0)=0;
    //Возвращает модель представления
    virtual ADarkChessGame* getChessGameModel()=0;

    //Устанавливает игрока, для которокого следует отображать доску
    virtual void setActivePlayer(ChessColor player)=0;
    //Возвращает активного игрока
    virtual ChessColor getActivePlayer()=0;

signals:
    //Срабатывает при перемещении фигуры
    virtual void pieceMovedByPlayer(ChessColor player,Piece piece,Tile from,Tile to)=0;
    //Срабатывает при превращении фигуры
    virtual void piecePromotedByPlayer(ChessColor player,TiledPiece from,TiledPiece to)=0;

};

Q_DECLARE_INTERFACE(IChessBoardView, "IChessBoardView")

#endif // ICHESSBOARDVIEW_H
