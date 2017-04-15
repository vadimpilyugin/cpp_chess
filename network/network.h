#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include <string>

#define DEBUG 0

class Thread
{
public:
	void static const wait(const int seconds) {
		boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
	}
};

class Broadcaster
{
public:
	Broadcaster();
	void start_broadcast(std::string msg);
	void stop_broadcast();
	~Broadcaster() { if(thread_p != nullptr) delete thread_p; }
private:
	// void wait(const int seconds) {
	//   boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
	// }
	boost::asio::io_service io;
	boost::asio::ip::udp::socket socket;
	boost::thread *thread_p;
	static const int wait_for = 1;
	bool interrupt_broadcast;
	void start_in_new_thread(std::string msg);
};

