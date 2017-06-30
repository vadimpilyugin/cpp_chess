#include "networkdarkchessgame.h"
#include "realchessconnector.h"
#include "printer.h"

NetworkDarkChessGame::NetworkDarkChessGame(IChessConnector *connector_, Player localPlayer_):isGreetingFinished(false),amIServer(false),
blockConvertion(false){
    connector=connector_;
    localPlayer=localPlayer_;
    amIServer=localPlayer_.color!=ChessColor::None;
    if(connector!=0){
        RealChessConnector *rcc=dynamic_cast<RealChessConnector*>(connector);
        Printer::passert(rcc != nullptr, "Wrong connector");
        QObject::connect(rcc,&RealChessConnector::receivedCommand,this,&NetworkDarkChessGame::slotDoCommand);
        if(!amIServer){
            GreetingCommand gc;
            gc.playerColor=localPlayer.color;
            gc.playerName=localPlayer.name;
            rcc->sendCommand(gc);
        }else{
            remotePlayer.color=(localPlayer.color==ChessColor::Black) ? ChessColor::White : ChessColor::Black;
        }
    }
    initialize();
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
            state=GameState::BlackGiveUp;
        else
            state=GameState::WhiteGiveUp;
        changeTurn();
    }
    else if (name.compare("OfferDrawCommand")==0){
        if (sendercolor==ChessColor::Black)
            state=GameState::BlackOfferDraw;
        else
            state=GameState::WhiteOfferDraw;
        changeTurn();
    }
    else if (name.compare("AcceptDrawCommand")==0){
        state=GameState::Draw;
        changeTurn();
    }
    else if (name.compare("RefuseDrawCommand")==0){
        state=GameState::Going;
        changeTurn();
    }
    else if (name.compare("GreetingCommand")==0){
        remotePlayer.name=dynamic_cast<GreetingCommand*>(command)->playerName;
    }
    else if (name.compare("TerminationCommand")==0){
        Printer::debug("Terminating engine");
        state=GameState::Termination;
    }
    else if (name.compare("Move")==0){
        if (!doMove(*(dynamic_cast<Move*>(command))))
            problems=true;
        if(getConvertionPieces(localPlayer).size()>0)blockConvertion=true;
    }
    else if (name.compare("PassCommand")==0){
        problems=true;
        if(blockConvertion){
            blockConvertion=false;
            problems=false;
        }
    }

    if ((!problems)&&(isitlocal))
        connector->sendCommand(*command);

    if(!problems && getConvertionPieces(remotePlayer).size()>0){
        PassCommand pc;pc.playerColor=localPlayer.color;
        connector->sendCommand(pc);
    }

    if(!problems && !blockConvertion)
        notifyObservers();

    delete command;
}

void NetworkDarkChessGame::slotDoCommand(Command *command){
    if(!isGreetingFinished){
        GreetingCommand * gc=dynamic_cast<GreetingCommand*>(command);
        if(gc!=0){
            remotePlayer.name=gc->playerName;
            if(amIServer){
                gc->playerColor=localPlayer.color;
                gc->playerName=localPlayer.name;
                connector->sendCommand(*gc);
                delete gc;
                if(localPlayer.color==ChessColor::Black){
                    isGreetingFinished=true;
                    notifyObservers();
                }
            }else{
                remotePlayer.color=gc->playerColor;
                localPlayer.color=(gc->playerColor==ChessColor::White) ? ChessColor::Black : ChessColor::White;
                if(localPlayer.color!=ChessColor::White){
                    PassCommand pc;
                    connector->sendCommand(pc);
                }
                isGreetingFinished=true;
                notifyObservers();
            }
        }else if(amIServer){
            isGreetingFinished=true;
            notifyObservers();
        }
    }else{
        doCommand(command);
    }
}

