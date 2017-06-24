build/client: build/client.o lib/libnetwork.a build/chess_connector.o
	g++ -o build/client build/client.o build/chess_connector.o ../common/bin/*.o -L lib/ -lnetwork -lzmq -lpthread
build/server: build/server.o lib/libnetwork.a build/chess_connector.o
	g++ -o build/server build/server.o build/chess_connector.o ../common/bin/*.o -L lib/ -lnetwork -lzmq -lpthread

.PHONY: clean
clean: 
	rm build/*

.PHONY: all
all: build/client build/server
.PHONY: run
run: all
	build/$(prog)

build/client.o: src/client.cpp
	g++ -o build/client.o -c src/client.cpp --std=c++11 -I include -I ../common
build/server.o: src/server.cpp
	g++ -o build/server.o -c src/server.cpp --std=c++11 -I include -I ../common
build/chess_connector.o: src/chess_connector.cpp
	g++ -o build/chess_connector.o -c src/chess_connector.cpp --std=c++11 -I include -I ../common
