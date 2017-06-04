#include "chess_connector.h"

int main () {
	// Подключаемся к серверу
	RealChessConnector client = RealChessConnector::connect ("127.0.0.1", "5555");
	// Посылаем привет серверу
	client.sendCommand (Command ("Hello from client"));
	Printer::debug ("Послали приветствие");
	// Ждем подключений
	Command command = client.receiveCommand ();
	Printer::debug (command.serialize (), "Получили ответ");
	return 0;
}