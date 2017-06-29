#ifndef ICHESSBOARDCONTROLLER_H
#define ICHESSBOARDCONTROLLER_H

#include "piece.h"
#include "tile.h"
class IChessBoardController{
public:
public slots:
    //Послать команду хода фигурой
    virtual void sendMoveCommand(ChessColor player,Piece piece,Tile from,Tile to)=0;
    //Послать команду превращения фигуры
    virtual void sendPromoteCommand(ChessColor player,TiledPiece from,TiledPiece to)=0;
};

Q_DECLARE_INTERFACE(IChessBoardController, "IChessBoardController")

#endif // ICHESSBOARDCONTROLLER_H
