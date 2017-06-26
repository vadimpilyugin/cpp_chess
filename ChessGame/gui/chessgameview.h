#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#include <QWidget>
#include "ichessobserver.h"
#include "adarkchessgame.h"
#include "darkchessboardview.h"
#include "networkdarkchessgame.h"

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

    virtual void setActivePlayer(ChessColor player);
    virtual ChessColor getActivePlayer();

    virtual void setPlayers(Player player1,Player player2);

signals:
    void gameEnded();

private slots:
    void offerDrawButtonReleased();
    void giveUpButtonReleased();

private:
    void initPlayersFromNDCG(NetworkDarkChessGame *ndcg);
    DarkChessBoardView *_cbw;
    AChessGame *_acg;
    Player _player1,_player2;
    ChessColor _activePlayer;
    Ui::ChessGameWidget *ui;
};

#endif // CHESSGAMEWIDGET_H
