#ifndef IDARKCHESSBOARDWIDGET_H
#define IDARKCHESSBOARDWIDGET_H

#include "ichessboardwidget.h"

class IDarkChessBoardWidget:public IChessBoardWidget{
public:
    //Скрыть ячейку
    virtual void hideTile(Tile tile)=0;
    //Отобразить ячейку
    virtual void showTile(Tile tile)=0;
    //Отобразить все ячейки
    virtual void showAllTiles()=0;
    //Скрыть все ячейки
    virtual void hideAllTiles()=0;
};

#endif // IDARKCHESSBOARDWIDGET_H
