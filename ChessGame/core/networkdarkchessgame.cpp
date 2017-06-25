#include "networkdarkchessgame.h"


NetworkDarkChessGame::NetworkDarkChessGame(IChessConnector *connector_, Player localPlayer_){
    connector=connector_;
    localPlayer=localPlayer_;
}

NetworkDarkChessGame::getLocalPlayer(){
    return localPlayer;
}

NetworkDarkChessGame::getRemotePlayer(){
    return remotePlayer;
}

NetworkDarkChessGame::doCommand(Command * command){
    std::string name=command->getClassName();
    bool isitlocal=false;
    bool problems=false;
    if (command->playerColor==localPlayer.color)
        isitlocal=true;
    ChessColor sendercolor;
    if (isitlocal)
        sendercolor=localPlayer.color;
    else
        sendercolor=remotePlayer.color;
    if (compare(name,"GiveUpCommand")==0){
        if (sendercolor==ChessColor::Black)
            gameState=GameState::BlackGiveUp;
        else
            gameState=GameState::WhiteGiveUp;
    }
    else if (compare(name,"OfferDrawCommand")==0){
        if (sendercolor==ChessColor::Black)
            gameState=GameState::BlackOfferDraw;
        else
            gameState=GameState::WhiteOfferDraw;
    }
    else if (compare(name,"GreetingCommand")==0){
        remotePlayer.name=dynamic_cast<GreetingCommand*>(command)->playerName;
    }
    else if (compare(name,"TerminationCommand")==0){
        gameState=GameState::Termination;
    }
    else if (compare(name,"Move")==0){
        if (!doMove(*(dynamic_cast<Move*>(command))))
            problems=true;
    }
    if ((!problems)&&(isitlocal))
        connector->sendCommand(*command);

}

