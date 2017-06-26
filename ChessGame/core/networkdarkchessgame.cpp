#include "networkdarkchessgame.h"
#include "real_chess_connector.h"

NetworkDarkChessGame::NetworkDarkChessGame(IChessConnector *connector_, Player localPlayer_){
    connector=connector_;
    localPlayer=localPlayer_;
    if(connector!=0){
        RealChessConnector *rcc=dynamic_cast<RealChessConnector*>(connector);
        QObject::connect(rcc,&RealChessConnector::receivedCommand,this,&NetworkDarkChessGame::slotDoCommand);
    }
}

Player NetworkDarkChessGame::getLocalPlayer(){
    return localPlayer;
}

Player NetworkDarkChessGame::getRemotePlayer(){
    return remotePlayer;
}

void NetworkDarkChessGame::doCommand(Command * command){
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
    if (name.compare("GiveUpCommand")==0){
        if (sendercolor==ChessColor::Black)
            gameState=GameState::BlackGiveUp;
        else
            gameState=GameState::WhiteGiveUp;
    }
    else if (name.compare("OfferDrawCommand")==0){
        if (sendercolor==ChessColor::Black)
            gameState=GameState::BlackOfferDraw;
        else
            gameState=GameState::WhiteOfferDraw;
    }
    else if (name.compare("GreetingCommand")==0){
        remotePlayer.name=dynamic_cast<GreetingCommand*>(command)->playerName;
    }
    else if (name.compare("TerminationCommand")==0){
        gameState=GameState::Termination;
    }
    else if (name.compare("Move")==0){
        if (!doMove(*(dynamic_cast<Move*>(command))))
            problems=true;
    }
    notifyObservers();
    if ((!problems)&&(isitlocal))
        connector->sendCommand(*command);

}

