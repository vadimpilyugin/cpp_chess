#include "chess_connector.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
	// Подключаемся к серверу
	RealChessConnector client = RealChessConnector::connect ("127.0.0.1", "5555");
	// Посылаем привет серверу
	client.sendCommand (Command ("Hello from client"));
	Printer::debug ("Послали приветствие");
	// Ждем подключений
	bool new_message = false;
	Command command;
	while (!new_message) {
		try {
			command = client.receiveCommand ();
			new_message = true;
		}
		catch (Network::NoMessagesException &exc) {
			sleep (1);
		}
	}
	Printer::debug (command.serialize (), "Получили ответ");
	return 0;
}