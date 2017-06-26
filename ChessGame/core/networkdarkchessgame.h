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
public:
    NetworkDarkChessGame(IChessConnector * connector_,Player localPlayer_ );
    Player getLocalPlayer();
    Player getRemotePlayer();
    void doCommand(Command *command); // FIXME(14): virtual void doCommand

public slots:
    void slotDoCommand(Command* command){
        doCommand(command);
    }

};
