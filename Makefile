# Compiler
CC=g++

# Compiler Flags
CFLAGS = -Wall -O3 -std=c++11
CXXFLAGS = $(CFLAGS)

.PHONY: clean

ChutesAndLadders: ChutesAndLadders.o
	$(CC) -o ChutesAndLadders ChutesAndLadders.o

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: ChutesAndLadders 

clean:
	rm -f ChutesAndLadders ChutesAndLadders.o
