#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chessgameview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    gcw=new GameConnectionWidget();
    grcw=new GameRecvConnectionWidget();
    ui->stackedWidget->addWidget(gcw);
    ui->stackedWidget->addWidget(grcw);

    QObject::connect(ui->connectGameButton,&QPushButton::released,this,&MainWindow::connectGame);
    QObject::connect(ui->createGameButton,&QPushButton::released,this,&MainWindow::createGame);

    QObject::connect(gcw,&GameConnectionWidget::connectionCreated,this,&MainWindow::gameConnectionCreated);
    QObject::connect(grcw,&GameRecvConnectionWidget::connectionCreated,this,&MainWindow::gameConnectionCreated);

    QObject::connect(gcw,&GameConnectionWidget::connectionCanceled,this,&MainWindow::gameConnectionCanceled);
    QObject::connect(grcw,&GameRecvConnectionWidget::connectionCanceled,this,&MainWindow::gameConnectionCanceled);

    QObject::connect(ui->exitButton,&QPushButton::released,this,&QMainWindow::close);

    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGame()
{
    grcw->clearInput();
    ui->stackedWidget->setCurrentWidget(grcw);
}

void MainWindow::connectGame()
{
    gcw->clearInput();
    ui->stackedWidget->setCurrentWidget(gcw);
}

void MainWindow::gameConnectionCreated(IChessConnector *connector, Player player)
{

}

void MainWindow::gameConnectionCanceled()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}
