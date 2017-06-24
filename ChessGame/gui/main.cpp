#include "mainwindow.h"
#include <QApplication>
#include "chessgameview.h"
#include "darkchessboardview.h"
#include "real_chess_connector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    std::string ipAddr="127.0.0.1";
    std::string port="5555";
    for(int i=0;i<10000;++i)bool df=false;
    RealChessConnector *client = RealChessConnector::bind(ipAddr, port);
    return a.exec();
}
