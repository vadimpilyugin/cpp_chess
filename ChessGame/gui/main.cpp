#include "mainwindow.h"
#include <QApplication>
#include "chessgameview.h"
#include "darkchessboardview.h"
#include "networkdarkchessgame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    NetworkDarkChessGame *cg=new NetworkDarkChessGame(0,{ChessColor::White,"dfkjfkj"});
    cg->initialize();

    ChessGameView *cgv=new ChessGameView(cg);
    cgv->setActivePlayer({ChessColor::White,"dkfjf"});
    cgv->show();
    cg->notifyObservers();

    return a.exec();
}
