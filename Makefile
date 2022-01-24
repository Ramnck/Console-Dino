CC=g++
SRCS=$(shell dir /b /s *.cpp)
CFLAGS=-s -g0 -DNDEBUG -w -I inc

all: main

main:
	$(CC) $(CFLAGS) $(SRCS) -o bin/dino
d: 
	$(CC) -I inc $(SRCS) -o dino