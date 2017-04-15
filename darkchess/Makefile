CC =g++
TARS = chesstest
OBJS = main.cpp chessrules.cpp
RM = rm -rf

all: $(TARS)

chessrules.o: chessgame.h basic.h dark.h chessrules.h chessrules.cpp
main.o: chessgame.h basic.h dark.h chessrules.h main.cpp chessrules.cpp

chesstest: main.o chessrules.o
	$(CC) $(CFLAGS) $^ -o $@ 
 
clean:
	$(RM)
