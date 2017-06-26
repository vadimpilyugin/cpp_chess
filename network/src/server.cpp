#include "real_chess_connector.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
	// Стартуем сервер
	RealChessConnector *server = RealChessConnector::bind ("127.0.0.1", "500");
	// Ждем подключений
	while (1) {
		try {
			Printer::error ("Has not connected");
			while (!server -> hasConnected ()) {
				sleep (1);
			}
			server -> receiveCommand ();
			Printer::debug ("Получили команду");
			server -> sendCommand (Move (Tile (3,14), Tile (100,100)));
		}
		catch (Network::NoMessagesException &exc) {
			sleep (1);
		}
	}
	return 0;
}
