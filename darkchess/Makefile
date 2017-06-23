CC =g++
TARS = chesstest
OBJS = main.cpp chessrules.cpp chessgame.cpp
RM = rm -rf

all: $(TARS)
chessgame.o:  chessgame.cpp chessrules.cpp chessgame.h basic.h dark.h
chessrules.o: chessgame.h basic.h dark.h chessrules.cpp
main.o: chessgame.h basic.h dark.h main.cpp chessrules.cpp chessgame.cpp

chesstest: main.o chessrules.o chessgame.o
	$(CC) $(CFLAGS) $^ -o $@ 
 
clean:
	$(RM)
