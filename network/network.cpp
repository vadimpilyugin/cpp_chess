#include "network.h"

const int port = 6666;

Broadcaster::Broadcaster(): io(), socket(io), interrupt_broadcast(false), thread_p(nullptr) { 
	boost::system::error_code error;
	socket.open(boost::asio::ip::udp::v4(), error);
    socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket.set_option(boost::asio::socket_base::broadcast(true));
    #if DEBUG
    std::cout << "Initialized Broadcaster\n";
    #endif
}

void Broadcaster::start_in_new_thread(std::string msg) {
	boost::asio::ip::udp::endpoint senderEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), port);
    for(int i = 0;; i++) {
		socket.send_to(boost::asio::buffer(msg.c_str(), msg.size()), senderEndpoint);
		#if DEBUG
		std::cout << "sent " << i+1 << " packets" << std::endl;
		#endif
		Thread::wait(wait_for);
		if(interrupt_broadcast)
			break;
    }
}

void Broadcaster::start_broadcast(std::string msg)
{
	interrupt_broadcast = false;
	if(thread_p == nullptr) {
		#if DEBUG
		std::cout << "Entered start_broadcast\n";
		#endif
		thread_p = new boost::thread(boost::bind(&Broadcaster::start_in_new_thread, this, msg));
	}
	#if DEBUG
	std::cout << "Main thread exit start_broadcast\n";
	#endif
}

void Broadcaster::stop_broadcast() {
	interrupt_broadcast = true;
	if(thread_p != nullptr) {
		#if DEBUG
		std::cout << "Main thread is going to join\n";
		#endif
		thread_p -> join();
	}
}


// class Receiver
// {
// 	Receiver();
// 	void start_receive();
// 	std::string end_receive();
// private:
// 	boost::asio::io_service io;
// 	boost::asio::ip::udp::socket socket;
// 	bool interrupt_receive;
// 	boost::thread *thread_p;
// 	std::tuple<string, string, int> start_in_new_thread();
// };

// Receiver::Receiver(): io(), socket(io), thread_p(nullptr) {
// 	boost::system::error_code error;
// 	socket.open(boost::asio::ip::udp::v4(), error);
//     #if DEBUG
//     std::cout << "Initialized Receiver\n";
//     #endif
// }

// void Receiver::start_receive() {
// 	if(thread_p == nullptr) {
// 		#if DEBUG
// 		std::cout << "Entered start_receive\n";
// 		#endif
// 		thread_p = new boost::thread(boost::bind(&Receiver::start_in_new_thread, this));
// 	}
// 	#if DEBUG
// 	std::cout << "Main thread exit start_broadcast\n";
// 	#endif
// }

// std::string Receiver::start_in_new_thread() {
// 	boost::asio::ip::udp::endpoint senderEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), port);
//     boost::array<char, 128> recv_buf;
//     size_t len = socket.receive_from(boost::asio::buffer(recv_buf), senderEndpoint);
// 	#if DEBUG
// 	std::cout << "received a packet! ";
// 	std::cout.write(recv_buf.data(), len);
// 	std::cout << std::endl;
// 	#endif
// 	return std::string(recv_buf);
// }

// std::string Receiver::end_receive() {

// }