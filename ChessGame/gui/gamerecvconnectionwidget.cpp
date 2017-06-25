#include "gamerecvconnectionwidget.h"
#include "ui_gamerecvconnectionwidget.h"

#include <string>
#include <QMovie>

const std::string GameRecvConnectionWidget::_port="7200";

GameRecvConnectionWidget::GameRecvConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameRecvConnectionWidget),
    _connector(0),_counter(0),_counterLimit(3000),_timerPeriod(100)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/Images/waiting.gif");
    ui->waitingLabel->setMovie(movie);
    movie->start();

    goToInputMode();
    clearInput();

    QObject::connect(ui->userLineEdit,&QLineEdit::textChanged,this,&GameRecvConnectionWidget::userNameChanged);
    QObject::connect(&_timer,&QTimer::timeout,this,&GameRecvConnectionWidget::connectionChecker);
    QObject::connect(ui->connectionButton,&QPushButton::released,this,&GameRecvConnectionWidget::connectButtonReleased);
    QObject::connect(ui->cancelButton,&QPushButton::released,this,&GameRecvConnectionWidget::cancelButtonReleased);
}

GameRecvConnectionWidget::~GameRecvConnectionWidget()
{
    delete ui;
    if(_connector!=0)delete _connector;
}

void GameRecvConnectionWidget::goToWaitingMode()
{
    _state=State::Waiting;
    ui->connectionButton->setText("Отменить ожидание соединени");
    ui->waitingLabel->setVisible(true);
    ui->statusLabel->setVisible(false);
}

void GameRecvConnectionWidget::goToErrorMode()
{
    _state=State::Error;
    ui->connectionButton->setText("Соединиться");
    ui->waitingLabel->setVisible(false);
    ui->statusLabel->setVisible(true);
}

void GameRecvConnectionWidget::goToInputMode()
{
    _state=State::Input;
    ui->connectionButton->setText("Ожидать соединение");
    ui->waitingLabel->setVisible(false);
    ui->statusLabel->setVisible(false);
}

void GameRecvConnectionWidget::clearInput()
{
    ui->userLineEdit->clear();
    ui->userLineEdit->setStyleSheet("border: 1px solid red");
}

void GameRecvConnectionWidget::userNameChanged(const QString &name)
{
    if(name.size()>0)ui->userLineEdit->setStyleSheet("border: 1px solid green");
    else ui->userLineEdit->setStyleSheet("border: 1px solid red");
}

void GameRecvConnectionWidget::connectButtonReleased()
{
    if(_state==State::Waiting){
        _timer.stop();
        if(_connector!=0)delete _connector;
        _connector=0;
        goToInputMode();
    }else{
        if(ui->userLineEdit->text().size()>0){
            goToWaitingMode();
            _counter=0;
            _connector=RealChessConnector::bind("*",_port);
            _timer.setInterval(_timerPeriod);
            _timer.start();
        }
    }
}

void GameRecvConnectionWidget::cancelButtonReleased()
{
    _timer.stop();
    if(_connector!=0)delete _connector;
    _connector=0;
    goToInputMode();
    emit connectionCanceled();
}

void GameRecvConnectionWidget::connectionChecker()
{
    ++_counter;
    if(_connector!=0){
        if(_connector->hasConnected()){
            _timer.stop();
            goToInputMode();
            RealChessConnector *cc=_connector;
            _connector=0;
            ChessColor color=ui->whiteButton->isChecked() ? ChessColor::White: ChessColor::Black;
            Player player;player.color=color;player.name=ui->userLineEdit->text().toStdString();
            emit connectionCreated(cc,player);
        }else{
            if(_counter>_counterLimit){
                _timer.stop();
                delete _connector;
                _connector=0;
                goToErrorMode();
            }
        }
    }else _timer.stop();
}
