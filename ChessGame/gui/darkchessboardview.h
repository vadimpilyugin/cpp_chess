#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include "ichessobserver.h"
#include "darkchessboardwidget.h"
#include "ichessboardview.h"
#include "adarkchessgame.h"

class DarkChessBoardView : public DarkChessBoardWidget,public IChessBoardView
{
    Q_OBJECT
    Q_INTERFACES(IChessBoardView)
public:
    DarkChessBoardView(ADarkChessGame *game=0, QWidget* parent=0);
    virtual ~DarkChessBoardView();

    virtual void update(AChessGame* game);

    virtual void setChessGameModel(ADarkChessGame* game=0);
    virtual ADarkChessGame* getChessGameModel();

    virtual void setActivePlayer(ChessColor player);
    virtual ChessColor getActivePlayer();

public slots:
    void hightlightMoves(Piece piece,Tile tile);
    void pieceMovedSlot(Piece piece,Tile from,Tile to);
    void piecePromotedSlot(TiledPiece from, TiledPiece to);

signals:
    void pieceMovedByPlayer(ChessColor player,Piece piece,Tile from,Tile to);
    void piecePromotedByPlayer(ChessColor player,TiledPiece from,TiledPiece to);

private:
    ChessColor _activePlayer;
    ADarkChessGame* _dcg;
};

#endif // CHESSBOARDVIEW_H
