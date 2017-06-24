#include "gameconnectionwidget.h"
#include "ui_gameconnectionwidget.h"

#include <string>
#include <QMovie>

bool isValidIPv4Block(std::string block) {
    int num = 0;
    if (block.size() > 0 && block.size() <= 3) {
        for (int i = 0; i < block.size(); i++) {
            char c = block[i];
            // special case: if c is a leading zero and there are characters left
            if (!isalnum(c) || (i == 0 && c == '0' && block.size() > 1))
            return false;
            else {
            num *= 10;
            num += c - '0';
            }
        }
        return num <= 255;
    }
    return false;
}

bool isValidIPv4(std::string ip) {
    size_t start=0;
    size_t end=ip.find_first_of('.');
    if(end==std::string::npos)return false;
    if(!isValidIPv4Block(ip.substr(start,end)))return false;
    int i=0;
    for(i;i<2;++i){
        start=end+1;
        end=ip.find_first_of('.',start);
        if(end==std::string::npos)return false;
        if(!isValidIPv4Block(ip.substr(start,end-start)))return false;
    }
    start=end+1;
    end=ip.find_first_of('.',start);
    if(end!=std::string::npos)return false;
    if(!isValidIPv4Block(ip.substr(start,end-start)))return false;
    return true;
}

const std::string GameConnectionWidget::_port="500";

GameConnectionWidget::GameConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameConnectionWidget),
    _connector(0),_counter(0),_counterLimit(30),_timerPeriod(100)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/Images/waiting.gif");
    ui->waitingLabel->setMovie(movie);
    movie->start();

    ui->statusLabel->setVisible(false);
    ui->waitingLabel->setVisible(false);

    QObject::connect(ui->ipLineEdit,&QLineEdit::textChanged,this,&GameConnectionWidget::ipAddressChanged);
    QObject::connect(&_timer,&QTimer::timeout,this,&GameConnectionWidget::connectionChecker);
    QObject::connect(ui->connectionButton,&QPushButton::released,this,&GameConnectionWidget::connectButtonReleased);
    QObject::connect(ui->cancelButton,&QPushButton::released,this,&GameConnectionWidget::cancelButtonReleased);
}

GameConnectionWidget::~GameConnectionWidget()
{
    delete ui;
    if(_connector!=0)delete _connector;
}

void GameConnectionWidget::ipAddressChanged(const QString &ip){
    std::string ipAddress=ip.toLatin1().data();
    if(isValidIPv4(ipAddress)){
        ui->ipLineEdit->setStyleSheet("border: 1px solid green");
    }else{
        ui->ipLineEdit->setStyleSheet("border: 1px solid red");
    }
}

void GameConnectionWidget::connectButtonReleased()
{
    std::string ipAddress=ui->ipLineEdit->text().toLatin1().data();
    if(ui->userLineEdit->text().size()>0 && isValidIPv4(ipAddress)){
        _counter=0;
        ui->statusLabel->setVisible(false);
        ui->waitingLabel->setVisible(true);
        _connector=RealChessConnector::connect(ipAddress,_port);
        _timer.setInterval(_timerPeriod);
        _timer.start();
    }
}

void GameConnectionWidget::cancelButtonReleased()
{
    _timer.stop();
    if(_connector!=0)delete _connector;
    _connector=0;
    ui->statusLabel->setVisible(false);
    ui->waitingLabel->setVisible(false);
    emit cancel();
}

void GameConnectionWidget::connectionChecker()
{
    ++_counter;
    if(_connector!=0){
        if(_connector->hasConnected()){
            ui->waitingLabel->setVisible(false);
            ui->statusLabel->setVisible(false);
            _timer.stop();
            RealChessConnector *cc=_connector;
            _connector=0;
            emit connectionCreated(cc);
        }else{
            if(_counter>_counterLimit){
                _timer.stop();
                delete _connector;
                _connector=0;
                ui->waitingLabel->setVisible(false);
                ui->statusLabel->setText("Connection is not completed!");
                ui->statusLabel->setVisible(true);
            }
        }
    }else _timer.stop();
}
