#include "chess_connector.h"

/*
* Имплементация интерфейса
*/

class RealChessConnector {
public:
	// Это метод для старта сервера. После вызова клиенты могут начать подключаться
	static RealChessConnector bind (std::string ip_addr = std::string("*"), std::string port = std::string("*"))
	throw 	(Exception::Exception);
	// Это метод для подключения к другому игроку
	static RealChessConnector connect (std::string ip_addr, std::string port)
	throw 	(Exception::Exception);
	virtual void sendCommand (const Command &command)
	throw (
		Exception::Exception,
		Network::WrongOrderException,
		Network::CannotSendException,
		Printer::AssertException
	);
	virtual Command *receiveCommand ()
	throw (
		Exception::Exception,
		Network::WrongOrderException, 
		Network::NoMessagesException
	);
private:
	RealChessConnector (Network::Socket &&socket_): socket(std::move(socket_)) {}
	Network::Socket socket;
};