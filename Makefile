CC=g++
SRCS=$(shell find . -name "*.cpp")
CFLAGS=-O3 -s -g0 -I inc
all: main

main:
	$(CC) $(CFLAGS) $(SRCS) -o start
