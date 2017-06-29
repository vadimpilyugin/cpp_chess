#include "darkchessboardview.h"
#include "adarkchessgame.h"
#include <vector>

const size_t rowCount=8;
const size_t colCount=8;

DarkChessBoardView::DarkChessBoardView(ADarkChessGame *game, QWidget* parent):DarkChessBoardWidget(parent),_dcg(game)
{
    QObject::connect(this,&DarkChessBoardWidget::pieceHover,this,&DarkChessBoardView::hightlightMoves);
    QObject::connect(this,&DarkChessBoardWidget::pieceMoved,this,&DarkChessBoardView::pieceMovedSlot);
    QObject::connect(this,&DarkChessBoardWidget::pieceConverted,this,&DarkChessBoardView::piecePromotedSlot);

    if(_dcg!=0) _dcg->attachObserver(this);
}

DarkChessBoardView::~DarkChessBoardView()
{
    if(_dcg!=0) _dcg->detachObserver(this);
}

void DarkChessBoardView::update(AChessGame *game)
{
    if(game==0)game=_dcg;
    if(game==0)return;

    for(int i=0;i<colCount;++i){
        for(int j=0;j<rowCount;++j){
            Tile tile(i+1,j+1);
            Piece piece=game->getPieceAtTile(tile);
            this->showTile(tile);
            this->setPieceAtTile(piece,tile);
        }
    }

    Player pl;pl.color=_activePlayer;

    ADarkChessGame *dcg=dynamic_cast<ADarkChessGame*>(game);
    if(dcg){

        vector<Tile> tiles=dcg->getHiddenTiles(pl);
        for(int i=0;i<tiles.size();++i){
            this->hideTile(tiles[i]);
        }
    }

    vector<TiledPiece> convertionPieces=game->getConvertionPieces(pl);
    if(convertionPieces.size())
        this->convertPiece(convertionPieces[0]);
    else this->hideConvert();
}

void DarkChessBoardView::setChessGameModel(ADarkChessGame *game)
{
    if(_dcg) _dcg->detachObserver(this);
    _dcg=game;
    update(_dcg);
}

ADarkChessGame *DarkChessBoardView::getChessGameModel()
{
    return _dcg;
}

void DarkChessBoardView::setActivePlayer(ChessColor player)
{
    _activePlayer=player;
    if(_activePlayer==ChessColor::White)setDirection(BoardDirection::TopRight);
    else setDirection(BoardDirection::BottomLeft);
    //ADD ACTIVE PLAY CONVERSION WITHOUTH UPDATE
}

ChessColor DarkChessBoardView::getActivePlayer()
{
    return _activePlayer;
}

void DarkChessBoardView::hightlightMoves(Piece piece, Tile tile)
{
    this->removeAllHighlights();
    if(_dcg!=0 && piece.type != PieceType::None){
        TiledPiece tiledPiece;
        tiledPiece.color=piece.color;
        tiledPiece.hasMoved=piece.hasMoved;
        tiledPiece.type=piece.type;
        tiledPiece.place=tile;
        std::vector<Tile> attackTiles=_dcg->getAttackTiles(tiledPiece);
        for(int i=0;i<attackTiles.size();++i){
            this->highlightAttackTile(attackTiles[i]);
        }
        std::vector<Tile> moveTiles=_dcg->getMoveTiles(tiledPiece);
        for(int i=0;i<moveTiles.size();++i){
            this->highlightMoveTile(moveTiles[i]);
        }
    }
}

void DarkChessBoardView::pieceMovedSlot(Piece piece, Tile from, Tile to)
{
    emit pieceMovedByPlayer(_activePlayer,piece,from,to);
}

void DarkChessBoardView::piecePromotedSlot(TiledPiece from, TiledPiece to)
{
    emit piecePromotedByPlayer(_activePlayer,from,to);
}
