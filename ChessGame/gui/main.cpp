#include "mainwindow.h"
#include <QApplication>
#include "chessgameview.h"
#include "darkchessboardview.h"
#include "real_chess_connector.h"
#include "gameconnectionwidget.h"
#include "gamerecvconnectionwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
