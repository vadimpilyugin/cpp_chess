#include "real_chess_connector.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
	// Стартуем сервер
	RealChessConnector server = RealChessConnector::bind ("127.0.0.1", "5555");
	// Ждем подключений
	bool new_message = false;
	Command *command;
	while (!new_message) {
		try {
			command = server.receiveCommand ();
			new_message = true;
		}
		catch (Network::NoMessagesException &exc) {
			sleep (1);
		}
	}
	Printer::debug (command -> serialize (), "Новое подключение");
	// Посылаем привет от сервера
	server.sendCommand (Move (Tile (3,14), Tile (100,100)));
	Printer::debug ("Послали приветствие");
	return 0;
}