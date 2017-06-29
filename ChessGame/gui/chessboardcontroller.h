#ifndef DARKCHESSBOARDCONTROLLER_H
#define DARKCHESSBOARDCONTROLLER_H

#include <QObject>
#include "ichessboardcontroller.h"
#include "achessgame.h"
#include <memory>

class ChessBoardController : public QObject,public IChessBoardController
{
    Q_OBJECT
    Q_INTERFACES(IChessBoardController)
public:
    ChessBoardController(AChessGame *game, QObject* parent=0);
public slots:
    void sendMoveCommand(ChessColor player,Piece piece,Tile from,Tile to);
    void sendPromoteCommand(ChessColor player,TiledPiece from,TiledPiece to);
private:
    AChessGame *_cg;
};

#endif // DARKCHESSBOARDCONTROLLER_H
