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

    _cbw=new DarkChessBoardView(this);
    ui->horizontalLayout->addWidget(_cbw);
    Tile tile;

    if(game!=0){
        for(int i=0;i<rowCount;++i){
            for(int j=0;j<colCount;++j){
                tile.x=j;
                tile.y=i;
                _cbw->setPieceAtTile(game->getPieceAtTile(tile),tile);
            }
        }
    }
}

ChessGameView::~ChessGameView()
{
    delete ui;
}


void ChessGameView::update(AChessGame *game){
    if(game!=0){
    }
}
