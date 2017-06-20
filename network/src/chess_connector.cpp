#include "chess_connector.h"

// Это метод для старта сервера. После вызова клиенты могут начать подключаться
RealChessConnector RealChessConnector::bind (std::string ip_addr, std::string port)
throw 	(Network::Exception)
{
	Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
	return RealChessConnector (std::move (Network::Socket::bind (endpoint.str())));
}
// Это метод для подключения к другому игроку
RealChessConnector RealChessConnector::connect (std::string ip_addr, std::string port)
throw 	(Network::Exception)
{
	Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
	return RealChessConnector (std::move (Network::Socket::connect (endpoint.str())));
}
void RealChessConnector::sendCommand (Command command)
throw (
	Network::Exception,
	Network::WrongOrderException,
	Network::CannotSendException,
	Printer::AssertException
)
{
	socket.send (command.serialize ());
}
Command RealChessConnector::receiveCommand ()
throw (
	Network::Exception,
	Network::WrongOrderException, 
	Network::NoMessagesException
)
{
	return Command (socket.recv ()); 
}