#include "darkchesslog.h"
#include <sstream>
#include <map>
#include "piece.h"

std::map<PieceType,std::string> getPieceCharMapping(){
    std::map<PieceType,std::string> res;
    res[PieceType::Pawn]="";
    res[PieceType::Rook]="R";
    res[PieceType::Bishop]="B";
    res[PieceType::Knight]="N";
    res[PieceType::Queen]="Q";
    res[PieceType::King]="K";
}

static const std::map<PieceType,std::string> pieceCharMapping=getPieceCharMapping();

DarkChessLog::DarkChessLog(ADarkChessGame *cg):_cg(cg)
{

}

DarkChessLog::~DarkChessLog()
{
    if(_cg)_cg->detachObserver(this);
}

void DarkChessLog::update(AChessGame *game)
{

}

std::string DarkChessLog::logToString()
{

}

std::string DarkChessLog::logToString(ChessColor player)
{

}
