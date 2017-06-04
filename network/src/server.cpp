#include "chess_connector.h"

int main () {
	// Стартуем сервер
	RealChessConnector server = RealChessConnector::bind ("127.0.0.1", "5555");
	// Ждем подключений
	Command command = server.receiveCommand ();
	Printer::debug (command.serialize (), "Новое подключение");
	// Посылаем привет от сервера
	server.sendCommand (Command ("Hello from server"));
	Printer::debug ("Послали приветствие");
	return 0;
}