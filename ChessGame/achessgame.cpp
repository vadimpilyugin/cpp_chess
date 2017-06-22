#include "achessgame.h"


void AChessGame::attachObserver(IChessObserver *observer){
    observers.insert(observer);
}

void AChessGame::detachObserver(IChessObserver *observer){
    observers.erase(observer);
}

AChessGame::AChessGame()
{

}
