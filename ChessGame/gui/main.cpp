#include "mainwindow.h"
#include <QApplication>
#include "chessgameview.h"
#include "darkchessboardview.h"
#include "networkdarkchessgame.h"
#include "real_chess_connector.h"

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
