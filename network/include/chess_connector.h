#include "network.h" // Sockets and Network:: namespace

/*
* Структура для передачи команд другой стороне. Сейчас просто как заглушка
*/

struct Command {
	std::string payload;
	Command (std::string payload_): payload(payload_) {}
	std::string serialize () { return payload; }
};

/*
* Интерфейс для работы с сетью
*/

class IChessConnector {
public:
	virtual void sendCommand (Command command)
	throw (
		Network::Exception,
		Network::WrongOrderException,
		Network::CannotSendException,
		Printer::AssertException
	) = 0;
	virtual Command receiveCommand ()
	throw (
		Network::Exception,
		Network::WrongOrderException, 
		Network::NoMessagesException
	) = 0;
};

/*
* Имплементация интерфейса
*/

class RealChessConnector {
public:
	// Это метод для старта сервера. После вызова клиенты могут начать подключаться
	static RealChessConnector bind (std::string ip_addr = std::string("*"), std::string port = std::string("*"))
	throw 	(Network::Exception)
	{
		Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
		return RealChessConnector (Network::Socket::bind (endpoint.str()));
	}
	// Это метод для подключения к другому игроку
	static RealChessConnector connect (std::string ip_addr, std::string port)
	throw 	(Network::Exception)
	{
		Network::TCPEndpoint endpoint = Network::TCPEndpoint(ip_addr, port);
		return RealChessConnector (Network::Socket::connect (endpoint.str()));
	}
	virtual void sendCommand (Command command)
	throw (
		Network::Exception,
		Network::WrongOrderException,
		Network::CannotSendException,
		Printer::AssertException
	)
	{
		socket.send (command.serialize ());
	}
	virtual Command receiveCommand ()
	throw (
		Network::Exception,
		Network::WrongOrderException, 
		Network::NoMessagesException
	)
	{
		return Command (socket.recv (false)); // включен блокирующий режим
	}
private:
	RealChessConnector (Network::Socket socket_): socket(socket_) {}
	Network::Socket socket;
};