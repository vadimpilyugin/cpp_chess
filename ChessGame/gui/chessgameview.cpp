#include "chessgameview.h"
#include "ui_chessgamewidget.h"

#include "darkchessboardview.h"

const size_t rowCount=8;
const size_t colCount=8;

ChessGameView::ChessGameView(ADarkChessGame *game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessGameWidget)
{
    ui->setupUi(this);

    _cbw=new DarkChessBoardView(game,this);
    ui->horizontalLayout->addWidget(_cbw);
    if(game)game->attachObserver(this);
}

ChessGameView::~ChessGameView()
{
    delete ui;
    //if
}


void ChessGameView::update(AChessGame *game){
    if(game!=0){
    }
}

void ChessGameView::setChessGameModel(AChessGame *game)
{

}

AChessGame *ChessGameView::getChessGameModel()
{

}

void ChessGameView::setActivePlayer(Player player)
{
    _activePlayer=player;
    _cbw->setActivePlayer(_activePlayer);
}

Player ChessGameView::getActivePlayer()
{
    return _activePlayer;
}
