#ifndef GAMECONNECTIONWIDGET_H
#define GAMECONNECTIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include "real_chess_connector.h"
#include "player.h"

namespace Ui {
class GameConnectionWidget;
}

class GameConnectionWidget : public QWidget
{
    Q_OBJECT
    enum class State{Waiting,Input,Error};
public:
    explicit GameConnectionWidget(QWidget *parent = 0);
    ~GameConnectionWidget();

    void goToWaitingMode();
    void goToErrorMode();
    void goToInputMode();

    void clearInput();

private slots:
    void ipAddressChanged(const QString& ip);
    void userNameChanged(const QString& name);
    void connectButtonReleased();
    void cancelButtonReleased();
    void connectionChecker();

signals:
    void connectionCreated(IChessConnector* rcc,Player player);
    void connectionCanceled();
private:
    QTimer _timer;
    Ui::GameConnectionWidget *ui;
    RealChessConnector* _connector;
    const static std::string _port;
    State _state;
    size_t _counter;
    size_t _counterLimit;
    size_t _timerPeriod;

};

#endif // GAMECONNECTIONWIDGET_H
