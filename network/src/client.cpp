#include "real_chess_connector.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
	// Подключаемся к серверу
	RealChessConnector *client = RealChessConnector::connect ("127.0.0.1", "5555");//RealChessConnector::connect ("194.87.96.23", "1234");
	client -> sendCommand (Move (Tile (666,666), Tile (13,13)));
	while (true) {
		try {
			Printer::error ("Has not connected");
			while (!client -> hasConnected ()) {
				sleep (1);
			}
			client -> receiveCommand ();
			break;
		}
		catch (Network::NoMessagesException &exc) {
			sleep (1);
		}
	}
	delete client;
	// while (n_messages < 5) {
	// 	try {
	// 		while (!(client -> hasConnected ()))
	// 			sleep (1);
	// 		
	// 		Printer::debug ("Послали приветствие");
	// 		
	// 		n_messages ++;
	// 	}

	// }
	// Printer::debug (command -> serialize (), "Получили ответ");
	return 0;
}