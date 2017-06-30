#ifndef GAMERECVCONNECTIONWIDGET_H
#define GAMERECVCONNECTIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include "player.h"
#include "realchessconnector.h"

namespace Ui {
class GameRecvConnectionWidget;
}

class GameRecvConnectionWidget : public QWidget
{
    Q_OBJECT
    enum class State{Waiting,Input,Error};
public:
    explicit GameRecvConnectionWidget(QWidget *parent = 0);
    ~GameRecvConnectionWidget();

    void clearInput();

private:
    void goToWaitingMode();
    void goToErrorMode();
    void goToInputMode();

private slots:
    void userNameChanged(const QString& name);
    void connectButtonReleased();
    void cancelButtonReleased();
    void connectionChecker();

signals:
    void connectionCreated(IChessConnector* rcc, Player color);
    void connectionCanceled();

private:
    QTimer _timer;
    Ui::GameRecvConnectionWidget *ui;
    RealChessConnector* _connector;
    const static std::string _port;
    State _state;
    size_t _counter;
    size_t _counterLimit;
    size_t _timerPeriod;
};

#endif // GAMERECVCONNECTIONWIDGET_H
