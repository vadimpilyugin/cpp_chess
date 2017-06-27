#include "darkchessboardview.h"
#include "adarkchessgame.h"
#include <vector>

const size_t rowCount=8;
const size_t colCount=8;

DarkChessBoardView::DarkChessBoardView(AChessGame *game,QWidget* parent):DarkChessBoardWidget(parent),_cg(game)
{
    QObject::connect(this,&DarkChessBoardWidget::pieceHover,this,&DarkChessBoardView::hightlightMoves);
    QObject::connect(this,&DarkChessBoardWidget::pieceMoved,this,&DarkChessBoardView::sendMoveCommand);
    QObject::connect(this,&DarkChessBoardWidget::pieceConverted,this,&DarkChessBoardView::sendConvertCommand);

    if(_cg!=0) _cg->attachObserver(this);
}

DarkChessBoardView::~DarkChessBoardView()
{
    if(_cg!=0) _cg->detachObserver(this);
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

void DarkChessBoardView::setChessGameModel(AChessGame *game)
{
    if(_cg) _cg->detachObserver(this);
    _cg=game;
    update(_cg);
}

AChessGame *DarkChessBoardView::getChessGameModel()
{
    return _cg;
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
    if(_cg!=0 && piece.type != PieceType::None){
        TiledPiece tiledPiece;
        tiledPiece.color=piece.color;
        tiledPiece.hasMoved=piece.hasMoved;
        tiledPiece.type=piece.type;
        tiledPiece.place=tile;
        std::vector<Tile> attackTiles=_cg->getAttackTiles(tiledPiece);
        for(int i=0;i<attackTiles.size();++i){
            this->highlightAttackTile(attackTiles[i]);
        }
//        std::vector<Tile> moveTiles=_cg->getMoveTiles(tiledPiece);
//        for(int i=0;i<moveTiles.size();++i){
//            this->highlightMoveTile(moveTiles[i]);
//        }
    }
}

void DarkChessBoardView::sendMoveCommand(Piece piece, Tile from, Tile to)
{
    Move* move=new Move();
    move->from=from;
    move->to=to;
    move->isConvertion=false;
    move->playerColor=_activePlayer;
    move->convertPiece=PieceType::None;
    _cg->doCommand(move);
    delete move;
    //setActivePlayer(_activePlayer==ChessColor::White ? ChessColor::Black : ChessColor::White);
}

void DarkChessBoardView::sendConvertCommand(TiledPiece piece, TiledPiece to)
{
    Move* move=new Move();
    move->from=piece.place;
    move->to=to.place;
    move->isConvertion=true;
    move->playerColor=_activePlayer;
    move->convertPiece=to.type;
    _cg->doCommand(move);
    delete move;
}
