#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ichessconnector.h"
#include "player.h"
#include "gameconnectionwidget.h"
#include "gamerecvconnectionwidget.h"
#include "chessgameview.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createGame();
    void connectGame();
    void gameEnded();

    void gameConnectionCreated(IChessConnector* connector,Player player);
    void gameConnectionCanceled();

    void deleteChessGame(){
        if(_cg!=0)delete _cg;
        _cg=0;
    }


private:
    GameConnectionWidget *_gcw;
    GameRecvConnectionWidget *_grcw;
    ChessGameView *_cgv;
    AChessGame *_cg;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
