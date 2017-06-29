#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkdarkchessgame.h"

#include "chessgameview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),_cg(0)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    setWindowTitle("Шахматы 1.0");

    _gcw=new GameConnectionWidget();
    _grcw=new GameRecvConnectionWidget();
    ui->stackedWidget->addWidget(_gcw);
    ui->stackedWidget->addWidget(_grcw);

    QObject::connect(ui->connectGameButton,&QPushButton::released,this,&MainWindow::connectGame);
    QObject::connect(ui->createGameButton,&QPushButton::released,this,&MainWindow::createGame);

    QObject::connect(_gcw,&GameConnectionWidget::connectionCreated,this,&MainWindow::gameConnectionCreated);
    QObject::connect(_grcw,&GameRecvConnectionWidget::connectionCreated,this,&MainWindow::gameConnectionCreated);

    QObject::connect(_gcw,&GameConnectionWidget::connectionCanceled,this,&MainWindow::gameConnectionCanceled);
    QObject::connect(_grcw,&GameRecvConnectionWidget::connectionCanceled,this,&MainWindow::gameConnectionCanceled);

    QObject::connect(ui->exitButton,&QPushButton::released,this,&QMainWindow::close);

    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGame()
{
    delete _cg;_cg=0;
    _grcw->clearInput();
    ui->stackedWidget->setCurrentWidget(_grcw);
}

void MainWindow::connectGame()
{
    delete _cg;_cg=0;
    _gcw->clearInput();
    ui->stackedWidget->setCurrentWidget(_gcw);
}

void MainWindow::gameEnded()
{
    _cg=_cgv->getChessGameModel();
    ui->stackedWidget->removeWidget(_cgv);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    _cgv->deleteLater();
    dynamic_cast<NetworkDarkChessGame*>(_cg)->stop();
}

void MainWindow::gameConnectionCreated(IChessConnector *connector, Player player)
{
    NetworkDarkChessGame *ndcg=new NetworkDarkChessGame(connector,player);
    _cgv=new ChessGameView(ndcg);
    QObject::connect(_cgv,&ChessGameView::gameEnded,this,&MainWindow::gameEnded);
    ui->stackedWidget->addWidget(_cgv);
    ui->stackedWidget->setCurrentWidget(_cgv);
}

void MainWindow::gameConnectionCanceled()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}
