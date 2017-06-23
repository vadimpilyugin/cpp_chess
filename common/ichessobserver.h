#ifndef ICHESSOBSERVER_H
#define ICHESSOBSERVER_H

#include "achessgame.h"

class IChessObserver
{
public:
    virtual void update(AChessGame* game)=0;
};

#endif // ICHESSOBSERVER_H
