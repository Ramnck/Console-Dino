CC=g++
CFLAGS=-O3 -s -g0
all: main

main:
	$(CC) $(CFLAGS) main.cpp 2d-lib.cpp -o start_game

