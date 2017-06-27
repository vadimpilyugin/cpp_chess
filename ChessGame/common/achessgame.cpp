#include "achessgame.h"
#include "ichessobserver.h"
#include "printer.h"

AChessGame::AChessGame(){

}

AChessGame::~AChessGame(){

}

void AChessGame::attachObserver(IChessObserver *observer){
    observers.insert(observer);
}

void AChessGame::detachObserver(IChessObserver *observer){
    observers.erase(observer);
}

void AChessGame::notifyObservers()
{
    Printer::debug("Notifying observers");
    set<IChessObserver*>::iterator it = observers.begin();
    for (it; it != observers.end(); ++it)
        (*it)->update(this);
}

GameState AChessGame::getState() {
    return state;
}
