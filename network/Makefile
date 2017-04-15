build/main.o: main.cpp
	g++ -std=c++11 -Wall -O2 -I /usr/local/boost_1_61_0 -c -o build/main.o main.cpp

build/network.o: network.cpp
	g++ -std=c++11 -Wall -O2 -I /usr/local/boost_1_61_0 -c -o build/network.o network.cpp

build/main: build/main.o build/network.o
	g++ -std=c++11 -Wall -O2 build/main.o build/network.o -o build/main -lboost_system -lboost_thread -lpthread
.PHONY: all
all: build/main

.PHONY: test
test: all
	build/main
.PHONY: clean
clean:
	rm build/*
