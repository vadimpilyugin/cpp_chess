#ifndef ICHESSLOG_H
#define ICHESSLOG_H

#include <string>
#include <chesscolor.h>
#include "ichessobserver.h"

class IChessLog
{
public:
    //Вернуть строку с записью ходов
    virtual std::string logToString()=0;
    //Вернуть строку с записью ходов только одного игрока
    virtual std::string logToString(ChessColor player)=0;
    //Добавить ход
    virtual void addMove(Move move)=0;
};

#endif // ICHESSLOG_H
