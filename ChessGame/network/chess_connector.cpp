#include "real_chess_connector.h"
#include "serialize.h"

const std::string RealChessConnector::heartbeat_port = "19363";
const std::string RealChessConnector::hello = "HELLO";
size_t RealChessConnector::connector_n = 0;

// Это метод для старта сервера. После вызова клиенты могут начать подключаться
RealChessConnector *RealChessConnector::bind (std::string ip_addr, std::string port)
throw 	(Exception::Exception)
{
    // Создаем контекст для сокетов
    Network::Context::createContext ();
    // Создаем пару сокетов для передачи команд
    Network::Socket command_sock = Network::Socket::bind ( 	Network::TCPEndpoint(ip_addr, port).str (),
                                                            Network::Context::getContext ());
    // Создаем пару сокетов для игры в картошку
    Network::Socket heartbeat_sock = Network::Socket::bind (Network::TCPEndpoint(ip_addr, heartbeat_port).str(),
                                                            Network::Context::getContext ());
    // Когда стартует сервер, он ждет сообщений от клиентов и не начинает игру
    return new RealChessConnector (std::move(command_sock), std::move(heartbeat_sock), false);
}
// Это метод для подключения к другому игроку
RealChessConnector *RealChessConnector::connect (std::string ip_addr, std::string port)
throw 	(Exception::Exception)
{
    // Создаем контекст для сокетов
    Network::Context::createContext ();
    // Создаем пару сокетов для передачи команд
    Network::Socket command_sock = Network::Socket::connect( Network::TCPEndpoint(ip_addr, port).str (),
                                                             Network::Context::getContext ());
    // Создаем пару сокетов для игры в картошку
    Network::Socket heartbeat_sock = Network::Socket::connect ( Network::TCPEndpoint(ip_addr, heartbeat_port).str(),
                                                                Network::Context::getContext ());
    // Когда стартует сервер, он ждет сообщений от клиентов и не начинает игру
    return new RealChessConnector (std::move (command_sock), std::move (heartbeat_sock), true);
}
bool RealChessConnector::pingOtherSide () throw (
    Network::WrongOrderException,
    Exception::Exception
)
{
    // Если горячая картошка у меня в руках, то я ее кидаю
    // Состояние сети подтвердить не могу
    if (hot_potato) {
        heartbeat_sock.send (hello);
        hot_potato = false;
        return false;
    }
    else {
        try {
            // Если ее у меня нет, то пытаюсь поймать
            heartbeat_sock.recv ();
            // как поймал, так сразу кидаю
            heartbeat_sock.send (hello);
            // поймать удалось, соединение подтверждено
            return true;
        }
        catch (Network::WrongOrderException &exc) {
            // Ошибка в протоколе: кинули картошку дважды
            Printer::error ("Дважды послали отклик", "RealChessConnector::hasConnected()");
            throw;
        }
        catch (Network::NoMessagesException &exc)
        {
            // Самая частая ошибка: картошка еще не прилетела
            Printer::note ("Отклик еще не пришел");
            return false;
        }
    }
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
    std::string received_command;
    received_command = socket.recv ();
    SerializedObject result (received_command);
    // Имя нужного класса команды
    std::string class_name = result.get ();
    // Произвести объект заданного класса, заполнить данными из полученной по сети информации
    return factory.get (class_name) -> deserialize (result.toString ());
}
