#include "network.h" // Sockets and Network:: namespace

/*
* Структура для передачи команд другой стороне. Сейчас просто как заглушка
*/

struct Command {
	std::string payload;
	Command (std::string payload_ = std::string()): payload(payload_) {}
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
	throw 	(Network::Exception);
	// Это метод для подключения к другому игроку
	static RealChessConnector connect (std::string ip_addr, std::string port)
	throw 	(Network::Exception);
	virtual void sendCommand (Command command)
	throw (
		Network::Exception,
		Network::WrongOrderException,
		Network::CannotSendException,
		Printer::AssertException
	);
	virtual Command receiveCommand ()
	throw (
		Network::Exception,
		Network::WrongOrderException, 
		Network::NoMessagesException
	);
private:
	RealChessConnector (Network::Socket &&socket_): socket(std::move(socket_)) {}
	Network::Socket socket;
};