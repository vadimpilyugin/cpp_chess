#ifndef CHESSLOG_H
#define CHESSLOG_H

#include "ichesslog.h"
#include "adarkchessgame.h"

class DarkChessLog:public IChessLog
{
public:
    DarkChessLog(){}
    virtual ~DarkChessLog();

private:
    std::vector<std::string> _whiteMoves,_blackMoves;
    Move _lastMove;
    // IChessLog interface
public:
    std::string logToString();
    std::string logToString(ChessColor player);

    // IChessLog interface
public:
    void addMove(Move move);
};

#endif // CHESSLOG_H
