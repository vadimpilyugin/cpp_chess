#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#include <QWidget>
#include "ichessobserver.h"
#include "adarkchessgame.h"
#include "darkchessboardview.h"

namespace Ui {
class ChessGameWidget;
}

class ChessGameView : public QWidget,public IChessObserver
{
    Q_OBJECT

public:
    explicit ChessGameView(ADarkChessGame *game,QWidget *parent = 0);
    ~ChessGameView();
    virtual void update(AChessGame *game);

private:
    DarkChessBoardView *_cbw;
    Ui::ChessGameWidget *ui;
};

#endif // CHESSGAMEWIDGET_H
