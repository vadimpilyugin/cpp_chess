#ifndef ICHESSLOG_H
#define ICHESSLOG_H

#include <string>
#include <chesscolor.h>
#include "ichessobserver.h"

class IChessLog:public IChessObserver
{
public:
    virtual std::string logToString()=0;
    virtual std::string logToString(ChessColor player)=0;
};

#endif // ICHESSLOG_H
