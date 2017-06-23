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

    //ui->tab_2->layout()->addWidget(new ChessGameView(0,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
