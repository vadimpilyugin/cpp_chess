#pragma once
#include "chess_connector.h"
#include "my_exception.h"

/*
* Имплементация интерфейса
*/

class NotYetConfirmedException: public Exception::Exception {
	using Exception::Exception;
};

class RealChessConnector {
public:
	// Это метод для старта сервера. После вызова клиенты могут начать подключаться
	static RealChessConnector *bind (std::string ip_addr = std::string("*"), std::string port = std::string("*"))
	throw 	(Exception::Exception);
	// Это метод для подключения к другому игроку
	static RealChessConnector *connect (std::string ip_addr, std::string port)
	throw 	(Exception::Exception);
	virtual void sendCommand (const Command &command)
	throw (
		Exception::Exception,
		Network::WrongOrderException,
		Network::CannotSendException,
		Printer::AssertException
	);
	virtual Command *receiveCommand (bool heartbeat = false)
	throw (
		Exception::Exception,
		Network::WrongOrderException, 
		Network::NoMessagesException
	);
	// Метод для проверки соединения.
	// NotYetConfirmException, если hot_potato == 0 и нет сообщений либо hot_potato == 1
	// True, если hot_potato == 0 и получено сообщение
	virtual bool hasConnected () throw (
		Network::WrongOrderException,
		Exception::Exception
	);
	~RealChessConnector () {
		socket.close ();
		heartbeat_sock.close ();
		connector_n --;
		if (connector_n == 0)
			Network::Context::destroyContext ();
	}
private:
	Network::Socket socket;
	/*
	* С момента подключения клиента к серверу, начинается игра в "горячуу картошку"
	* Тот, кто держит картошку, должен перебросить ее другому. Если другой не перебрасывает
	* обратно за разумное время, то считается, что тот вышел из игры. У кого сейчас картошка,
	* тот может выполнить hasConnected() и бросить ее другому. У кого нет, тот выполняет
	* hasConnected() и либо ловит картошку, либо выходит по исключению, что картошку пока
	* не бросили. Таким образом, один бросает, другой ловит и бросает обратно, а первый пони-
	* мает, что второй еще в игре. Дальше первый бросает второму и второй понимает, что 
	* первый в игре. И так далее.
	*/
	bool hot_potato;
	static const std::string heartbeat_port;
	static size_t connector_n;
	// У игры в картошку своя пара сокетов
	Network::Socket heartbeat_sock;
	RealChessConnector (Network::Socket &&socket_, Network::Socket &&heartbeat_sock_, bool hot_potato_): 
		socket (std::move (socket_)), hot_potato (hot_potato_), 
		heartbeat_sock (std::move (heartbeat_sock_))
		{
			if (hot_potato)
				hasConnected ();
			connector_n ++;
		}
};