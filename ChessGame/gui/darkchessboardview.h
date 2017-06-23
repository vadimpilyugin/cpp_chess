#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include "ichessobserver.h"
#include "darkchessboardwidget.h"

class DarkChessBoardView : public DarkChessBoardWidget,public IChessObserver
{
    Q_OBJECT
public:
    DarkChessBoardView(QWidget* parent=0);

    virtual void update(AChessGame* game);

    virtual void setChessGameModel(AChessGame* game=0);
    virtual AChessGame* getChessGameModel();

    virtual void setActivePlayer(Player player);
    virtual Player getActivePlayer();

public slots:
    void hightlightMoves(Piece piece,Tile tile);
    void sendMoveCommand(Piece piece,Tile from,Tile to);
    void sendConvertCommand(TiledPiece piece,TiledPiece to);
private:
    Player _activePlayer;
    AChessGame* _cg;
};

#endif // CHESSBOARDVIEW_H
