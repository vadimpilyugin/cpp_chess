#include "achessgame.h"


void AChessGame::attachObserver(IChessObserver *observer){
    observers.insert(observer);
}

void AChessGame::detachObserver(IChessObserver *observer){
    observers.erase(observer);
}

void AChessGame::notifyObservers()
{
    set<IChessObserver*>::iterator it = observers.begin();
    for (it; it != observers.end(); ++it)
        (*it)->update(this);
}

AChessGame::AChessGame()
{

}
