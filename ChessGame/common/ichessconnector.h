#pragma once
#include "network.h" // Sockets and Network:: namespace
#include "command.h"

/*
* Интерфейс для работы с сетью
*/

class IChessConnector {
public:
    virtual ~IChessConnector(){}
    virtual void sendCommand (const Command &command)
    throw (
        Exception::Exception,
        Network::WrongOrderException,
        Network::CannotSendException,
        Printer::AssertException
    ) = 0;
    virtual Command *receiveCommand ()
    throw (
        Exception::Exception,
        Network::WrongOrderException,
        Network::NoMessagesException
    ) = 0;
    virtual bool hasConnected () NOEXCEPT = 0;
};
