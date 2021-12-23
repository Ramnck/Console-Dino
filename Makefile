CC=g++
ifeq ($(OS),Windows_NT)
	SRCS=$(shell dir /b /s *.cpp)
else
	SRCS=$(shell find . -name "*.cpp")
endif
CFLAGS=-O3 -s -g0 -I inc
all: main

main:
#	$(CC) $(CFLAGS) $(SRCS) -o Dino
	$(CC) $(CFLAGS) src/2d-lib.cpp src/main.cpp -o dino

bmp:
	$(CC) $(CFLAGS) src/bmp-to-array.cpp -o bmp