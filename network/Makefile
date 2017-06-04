build/client: build/client.o lib/libnetwork.a
	g++ -o build/client build/client.o -L lib/ -lnetwork -lzmq -lpthread
build/server: build/server.o lib/libnetwork.a
	g++ -o build/server build/server.o -L lib/ -lnetwork -lzmq -lpthread

.PHONY: all
all: build/client build/server
.PHONY: test
test: all
	./build/server
	./build/client

build/client.o: src/client.cpp
	g++ -o build/client.o -c src/client.cpp --std=c++11 -I include
build/server.o: src/server.cpp
	g++ -o build/server.o -c src/server.cpp --std=c++11 -I include
