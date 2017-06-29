#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chess_connector.h"
#include "player.h"
#include "gameconnectionwidget.h"
#include "gamerecvconnectionwidget.h"
#include "chessgameview.h"

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

private:
    GameConnectionWidget *_gcw;
    GameRecvConnectionWidget *_grcw;
    ChessGameView *_cgv;
    AChessGame *_cg;


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
