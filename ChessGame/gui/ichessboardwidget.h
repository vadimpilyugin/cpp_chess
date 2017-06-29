#ifndef ICHESSBOARDWIDGET_H
#define ICHESSBOARDWIDGET_H

#include "tile.h"
#include "piece.h"

enum class BoardDirection{TopRight,BottomRight,TopLeft,BottomLeft};

class IChessBoardWidget{
public:
    //Подсветить ячейку, как ячейку, на которую можно передвинуть фигуру
    virtual void highlightMoveTile(Tile tile)=0;
    //Подсветить ячейку, как ячейку, на которой можно съесть фигуру
    virtual void highlightAttackTile(Tile tile)=0;
    //Удлаить подсветку на ячейке
    virtual void removeHighlightAtTile(Tile tile)=0;
    //Удалить все подсветки
    virtual void removeAllHighlights()=0;
    //Установить фигуру на ячейке
    virtual void setPieceAtTile(Piece piece,Tile tile)=0;
    virtual void setPieceAtTile(TiledPiece piece)=0;
    //Получить фигуру на ячейке
    virtual Piece getPieceAtTile(Tile tile)=0;
    //Удалить фигуру с ячейки
    virtual void removePieceAtTile(Tile tile)=0;
};

#endif // ICHESSBOARDWIDGET_H
