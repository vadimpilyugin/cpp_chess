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
    w.showMaximized();

    QMessageBox mb(0);
    mb.setWindowTitle("Предложение ничьи");
    mb.setText("Ваш соперник предложил. Желаете принять предложение?");
    mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mb.setDefaultButton(QMessageBox::Ok);
    int ret = mb.exec();
    switch(ret){
    case QMessageBox::Ok:
        ret=100;
        break;
    case QMessageBox::Cancel:
        ret=200;
        break;
    }

    return a.exec();
}
