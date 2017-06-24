#pragma once
#include "chess_connector.h"
#include "my_exception.h"
#include <QObject>

/*
* Имплементация интерфейса
*/

class RealChessConnector: public QObject {
    Q_OBJECT
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
    virtual Command *receiveCommand ()
    throw (
        Exception::Exception,
        Network::WrongOrderException,
        Network::NoMessagesException
    );
    // Метод для проверки соединения. True, если в последнем n-секундном
    // интервале был пинг, иначе False
    bool hasConnected () NOEXCEPT {
        return connection_state;
    }

public slots:
    /*
     * Метод для проверки соединения, только уже через
     * Qt-шный вызов. Фактически, в главном цикле его
     * вызывают по таймеру раз в n секунд и он сбрасывает
     * флаг соединения, чтобы мелкие таймеры его снова установили
     */
    void resetConnectionStatus () {
        if (first_time) {
            first_time = !first_time;
            connection_state = true;
        }
        else {
            connection_state = false;
        }
        // reset timer
    }
    /*
     * Метод для проверки соединения. Каждый раз, когда
     * его вызывают, он может установить флаг соединения
     * в true. В этом случае считается, что весь большой
     * интервал времени соединение есть.
    */
    void updateConnectionStatus () {
        if (pingOtherSide()) {
            connection_state = true;
        }
        // reset timer
    }
    /*
     * Метод, проверяющий, есть ли команды. Если есть, он
     * испускает сигнал receivedCommand
    */
    void checkCommands () {
        try {
            Command *command = receiveCommand();
            emit receivedCommand(command);
        }
        catch (Network::NoMessagesException &exc) {
            // команд пока нет
            // reset timer
        }
    }

signals:
    void receivedCommand (Command *command);
public:
    ~RealChessConnector () {
        socket.close ();
        heartbeat_sock.close ();
        connector_n --;
        if (connector_n == 0)
            Network::Context::destroyContext ();
    }
private:
    // Метод для проверки соединения.
    // False, если hot_potato == 0 и нет сообщений либо hot_potato == 1
    // True, если hot_potato == 0 и получено сообщение
    virtual bool pingOtherSide () throw (
        Network::WrongOrderException,
        Exception::Exception
    );
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
    static const std::string hello;
    static size_t connector_n;
    // У игры в картошку своя пара сокетов
    Network::Socket heartbeat_sock;
    RealChessConnector (Network::Socket &&socket_, Network::Socket &&heartbeat_sock_, bool hot_potato_):
        socket (std::move (socket_)), hot_potato (hot_potato_),
        heartbeat_sock (std::move (heartbeat_sock_)), connection_state (false), first_time (true)
        {
            if (hot_potato)
                hasConnected ();
            connector_n ++;
        }
    bool connection_state;
    bool first_time;
};
