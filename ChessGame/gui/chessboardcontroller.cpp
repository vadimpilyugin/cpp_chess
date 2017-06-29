#include "chessboardcontroller.h"
#include <memory>

ChessBoardController::ChessBoardController(AChessGame *game, QObject *parent):QObject(parent),_cg(game)
{
}

void ChessBoardController::sendMoveCommand(ChessColor player, Piece piece, Tile from, Tile to){
    Move * move=new Move();
    move->from=from;
    move->to=to;
    move->isConvertion=false;
    move->playerColor=player;
    move->convertPiece=PieceType::None;
    _cg->doCommand(move);
}

void ChessBoardController::sendPromoteCommand(ChessColor player, TiledPiece from, TiledPiece to){
    Move *move=new Move();
    move->from=from.place;
    move->to=to.place;
    move->isConvertion=true;
    move->playerColor=player;
    move->convertPiece=to.type;
    _cg->doCommand(move);
}
