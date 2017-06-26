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
    explicit ChessGameView(ADarkChessGame *game=0,QWidget *parent = 0);
    ~ChessGameView();
    virtual void update(AChessGame *game);

    virtual void setChessGameModel(AChessGame* game=0);
    virtual AChessGame *getChessGameModel();

    virtual void setActivePlayer(Player player);
    virtual Player getActivePlayer();

private:
    DarkChessBoardView *_cbw;
    AChessGame *_acg;
    Player _activePlayer;
    Ui::ChessGameWidget *ui;
};

#endif // CHESSGAMEWIDGET_H
