#pragma once
#include "adarkchessgame.h"
#include "ichessconnector.h"
#include <QObject>

class NetworkDarkChessGame:public QObject,public ADarkChessGame{
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
    ~NetworkDarkChessGame();
    Player getLocalPlayer();
    Player getRemotePlayer();
    virtual void doCommand(Command *command);

public slots:
    void slotDoCommand(Command* command);

};
