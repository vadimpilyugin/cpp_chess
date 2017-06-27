#pragma once
#include "chess_connector.h"
#include "my_exception.h"
#include <QObject>
#include <QTimer>

/*
* Имплементация интерфейса
*/

class RealChessConnector: public QObject,public IChessConnector {
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
    void resetConnectionState () {
        if (connection_state == false) {
            Command *command = new TerminationCommand();
            Printer::error("Connection lost");
            emit receivedCommand(command);
        }
        connection_state = false;
        // reset timer
    }
    /*
     * Метод для проверки соединения. Каждый раз, когда
     * его вызывают, он может установить флаг соединения
     * в true. В этом случае считается, что весь большой
     * интервал времени соединение есть.
    */
    void updateConnectionState () {
        if(connection_state == false)
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
    static const int big_interval = 10000; // 10 s
    static const int small_interval = 100; // 100 ms
    static const int command_check_interval = 3000; // 3 s
    static const std::string heartbeat_port;
    static const std::string hello;
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
    static size_t connector_n;
    // У игры в картошку своя пара сокетов
    Network::Socket heartbeat_sock;
    RealChessConnector (Network::Socket &&socket_, Network::Socket &&heartbeat_sock_, bool hot_potato_, bool isServer):
        socket (std::move (socket_)), hot_potato (hot_potato_),
        heartbeat_sock (std::move (heartbeat_sock_)), connection_state (false),
        big_timer (nullptr), small_timer (nullptr)
        {
            connector_n ++;
            big_timer.setInterval (big_interval);
            small_timer.setInterval(small_interval);
            command_check_timer.setInterval(command_check_interval);
            QObject::connect(&big_timer, SIGNAL(timeout()), this, SLOT(resetConnectionState()));
            QObject::connect(&small_timer, SIGNAL(timeout()), this, SLOT(updateConnectionState()));
            QObject::connect(&command_check_timer, SIGNAL(timeout()), this, SLOT(checkCommands()));
            big_timer.start();
            small_timer.start();
            // Не стартовать до первого send или receive
            // Сервер должен сразу начать слушать
            if (isServer)
                command_check_timer.start();
        }
    bool connection_state;
    QTimer big_timer;
    QTimer small_timer;
    QTimer command_check_timer;
};
