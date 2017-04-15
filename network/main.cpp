#include "network.h"

int main()
{
	Broadcaster b;
	b.start_broadcast("Help!");
	Thread::wait(10);
	b.stop_broadcast();

	
	return 0;
}