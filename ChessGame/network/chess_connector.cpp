#include "real_chess_connector.h"
#include "serialize.h"

// Это метод для старта сервера. После вызова клиенты могут начать подключаться
RealChessConnector RealChessConnector::bind (std::string ip_addr, std::string port)
throw 	(Exception::Exception)
{
	Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
	return RealChessConnector (std::move (Network::Socket::bind (endpoint.str())));
}
// Это метод для подключения к другому игроку
RealChessConnector RealChessConnector::connect (std::string ip_addr, std::string port)
throw 	(Exception::Exception)
{
	Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
	return RealChessConnector (std::move (Network::Socket::connect (endpoint.str())));
}
void RealChessConnector::sendCommand (const Command &command)
throw (
	Exception::Exception,
	Network::WrongOrderException,
	Network::CannotSendException,
	Printer::AssertException
)
{
	socket.send (command.serialize ());
}
Command *RealChessConnector::receiveCommand ()
throw (
	Exception::Exception,
	Network::WrongOrderException, 
	Network::NoMessagesException
)
{
	// Необходимо произвести один из типов команд
    CommandFactory factory;
	std::string received_command = socket.recv ();
	SerializedObject result (received_command);
	// Имя нужного класса команды
	std::string class_name = result.get ();
	// Произвести объект заданного класса, заполнить данными из полученной по сети информации
	return factory.get (class_name) -> deserialize (result.toString ());
}
