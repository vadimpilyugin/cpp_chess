#include "darkchesslog.h"
#include <sstream>
#include <iomanip>
#include <map>
#include "piece.h"
#include <algorithm>

static std::map<PieceType,std::string> getPieceCharMapping(){
    std::map<PieceType,std::string> res;
    res[PieceType::Pawn]="";
    res[PieceType::Rook]="R";
    res[PieceType::Bishop]="B";
    res[PieceType::Knight]="N";
    res[PieceType::Queen]="Q";
    res[PieceType::King]="K";
    return res;
}

static const std::map<PieceType,std::string> pieceCharMapping=getPieceCharMapping();

static std::string rowIndexToNotation(int row){
    return std::to_string(row);
}

static std::string colIndexToNotation(int col){
    char letter[]="A";
    letter[0]+=col-1;
    return std::string(letter);
}

DarkChessLog::~DarkChessLog()
{
}

std::string DarkChessLog::logToString()
{
    std::stringstream logStream;
    for(int i=0;i<std::min(_whiteMoves.size(),_blackMoves.size());++i){
        logStream<<std::setw(4)<<i+1<<" "<<_whiteMoves[i]<<" "<<_blackMoves[i]<<std::endl;
    }
    return logStream.str();
}

std::string DarkChessLog::logToString(ChessColor player)
{
    std::vector<std::string> &temp=player==ChessColor::White ? _whiteMoves : _blackMoves;
    std::stringstream logStream;
    for(int i=0;i<temp.size();++i){
        logStream<<std::setw(4)<<i+1<<" "<<temp[i]<<std::endl;
    }
    return logStream.str();
}

void DarkChessLog::addMove(Move move)
{
    if(!(move.to.x==move.from.x && move.to.y==move.from.y) && !(move==_lastMove)){
        std::string note=colIndexToNotation(move.from.x)+rowIndexToNotation(move.from.y)+"-";
        note+=colIndexToNotation(move.to.x)+rowIndexToNotation(move.to.y);
        if(move.playerColor==ChessColor::White)_whiteMoves.push_back(note);
        else if(move.playerColor==ChessColor::Black)_blackMoves.push_back(note);
    }
    _lastMove=move;
}
