#pragma once
#include "darkchessgame.h"
#include "chess_connector.h"
#include <QObject>

class NetworkDarkChessGame:public QObject,public DarkChessGame{
    Q_OBJECT
private:
    IChessConnector * connector;
    Player localPlayer;
    Player remotePlayer;
    bool isGreetingFinished;
    bool amIServer;
    bool blockConvertion;
public:
    NetworkDarkChessGame(IChessConnector * connector_,Player localPlayer_ );
    Player getLocalPlayer();
    Player getRemotePlayer();
    virtual void doCommand(Command *command);

public slots:
    void slotDoCommand(Command* command);

};
