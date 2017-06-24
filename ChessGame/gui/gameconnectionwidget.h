#ifndef GAMECONNECTIONWIDGET_H
#define GAMECONNECTIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include "real_chess_connector.h"

namespace Ui {
class GameConnectionWidget;
}

class GameConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameConnectionWidget(QWidget *parent = 0);
    ~GameConnectionWidget();

private slots:
    void ipAddressChanged(const QString& ip);
    void connectButtonReleased();
    void cancelButtonReleased();
    void connectionChecker();

signals:
    void connectionCreated(RealChessConnector* rcc);
    void cancel();
private:
    QTimer _timer;
    Ui::GameConnectionWidget *ui;
    RealChessConnector* _connector;
    const static std::string _port;
    size_t _counter;
    size_t _counterLimit;
    size_t _timerPeriod;

};

#endif // GAMECONNECTIONWIDGET_H
