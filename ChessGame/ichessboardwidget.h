#ifndef ICHESSBOARDWIDGET_H
#define ICHESSBOARDWIDGET_H
#include "types.h"

class IChessBoardWidget{
public:
    virtual void highlightMoveTile(Tile tile)=0;
    virtual void highlightAttackTile(Tile tile)=0;
    virtual void removeHighlightAtTile(Tile tile)=0;
    virtual void removeAllHighlights()=0;
    virtual void setPieceAtTile(Piece piece,Tile tile)=0;
    virtual void setPieceAtTile(TiledPiece piece)=0;
    virtual Piece getPieceAtTile(Tile tile)=0;
    virtual void removePieceAtTile(Tile tile)=0;
};

#endif // ICHESSBOARDWIDGET_H
