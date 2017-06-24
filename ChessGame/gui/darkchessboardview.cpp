#include "darkchessboardview.h"
#include "adarkchessgame.h"
#include <vector>

const size_t rowCount=8;
const size_t colCount=8;

DarkChessBoardView::DarkChessBoardView(QWidget* parent):DarkChessBoardWidget(parent),_cg(0)
{
    QObject::connect(this,&DarkChessBoardWidget::pieceHover,this,&DarkChessBoardView::hightlightMoves);
    QObject::connect(this,&DarkChessBoardWidget::pieceMoved,this,&DarkChessBoardView::sendMoveCommand);
    QObject::connect(this,&DarkChessBoardWidget::pieceConverted,this,&DarkChessBoardView::sendConvertCommand);
}

void DarkChessBoardView::update(AChessGame *game)
{
    if(game==0)game=_cg;
    if(game==0)return;

    for(int i=0;i<colCount;++i){
        for(int j=0;j<rowCount;++j){
            Tile tile(i+1,j+1);
            Piece piece=game->getPieceAtTile(tile);
            this->showTile(tile);
            this->setPieceAtTile(piece,tile);
        }
    }

    ADarkChessGame *dcg=dynamic_cast<ADarkChessGame*>(game);
    if(dcg){
        vector<Tile> tiles=dcg->getHiddenTiles(_activePlayer);
        for(int i=0;i<tiles.size();++i){
            this->hideTile(tiles[i]);
        }
    }

    vector<TiledPiece> convertionPieces=game->getConvertionPieces(_activePlayer);
    if(convertionPieces.size())
        this->convertPiece(convertionPieces[0]);
}

void DarkChessBoardView::setChessGameModel(AChessGame *game)
{
    _cg=game;
    update(_cg);
}

AChessGame *DarkChessBoardView::getChessGameModel()
{
    return _cg;
}

void DarkChessBoardView::setActivePlayer(Player player)
{
    _activePlayer=player;
    if(_activePlayer.color==ChessColor::White)setDirection(BoardDirection::TopRight);
    else setDirection(BoardDirection::BottomLeft);
}

Player DarkChessBoardView::getActivePlayer()
{
    return _activePlayer;
}

void DarkChessBoardView::hightlightMoves(Piece piece, Tile tile)
{
    this->removeAllHighlights();
    if(_cg!=0){
        TiledPiece tiledPiece;
        tiledPiece.color=piece.color;
        tiledPiece.hasMoved=piece.hasMoved;
        tiledPiece.type=piece.type;
        tiledPiece.place=tile;
        std::vector<Tile> attackTiles=_cg->getAttackTiles(tiledPiece);
        for(int i=0;i<attackTiles.size();++i){
            this->highlightAttackTile(attackTiles[i]);
        }
        std::vector<Tile> moveTiles=_cg->getMoveTiles(tiledPiece);
        for(int i=0;i<moveTiles.size();++i){
            this->highlightMoveTile(moveTiles[i]);
        }
    }
}

void DarkChessBoardView::sendMoveCommand(Piece piece, Tile from, Tile to)
{
    Move* move=new Move();
    move->from=from;
    move->to=to;
    move->isConvertion=false;
    move->playerColor=_activePlayer.color;
    move->convertPiece=PieceType::None;
    _cg->doCommand(move);
    delete move;
}

void DarkChessBoardView::sendConvertCommand(TiledPiece piece, TiledPiece to)
{
    Move* move=new Move();
    move->from=piece.place;
    move->to=to.place;
    move->isConvertion=true;
    move->playerColor=_activePlayer.color;
    move->convertPiece=to.type;
    _cg->doCommand(move);
    delete move;
}
