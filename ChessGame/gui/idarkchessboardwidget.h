#ifndef IDARKCHESSBOARDWIDGET_H
#define IDARKCHESSBOARDWIDGET_H

#include "ichessboardwidget.h"

class IDarkChessBoardWidget:public IChessBoardWidget{
public:
    virtual void hideTile(Tile tile)=0;
    virtual void showTile(Tile tile)=0;
    virtual void showAllTiles()=0;
    virtual void hideAllTiles()=0;
};

#endif // IDARKCHESSBOARDWIDGET_H
