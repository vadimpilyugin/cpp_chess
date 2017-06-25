#pragma once
#include "darkchessgame.h"

class NetworkDarkChessGame:public DarkChessGame{
private:
    IChessConnector * connector;
    Player localPlayer;
    Player remotePlayer;
public:
    NetworkDarkChessGame(IChessConnector * connector_,Player localPlayer_ );
    Player getLocalPlayer();
    Player getRemotePlayer();
    void doCommand(Command *command);

};