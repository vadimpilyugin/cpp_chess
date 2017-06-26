#ifndef CHESSLOG_H
#define CHESSLOG_H

#include "ichesslog.h"
#include "adarkchessgame.h"

class DarkChessLog:public IChessLog
{
public:
    DarkChessLog(ADarkChessGame *cg);
    virtual ~DarkChessLog();

private:
    ADarkChessGame *_cg;
    std::vector<std::string> _whiteMoves,_blackMoves;
    Move _lastMove;

    // IChessObserver interface
public:
    void update(AChessGame *game);

    // IChessLog interface
public:
    std::string logToString();
    std::string logToString(ChessColor player);
};

#endif // CHESSLOG_H
