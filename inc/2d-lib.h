#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <conio.h>

#define UP true
#define DOWN false
#define RESET -1

#define IMG_H 16
#define IMG_W 16

#define BACK_H 16

#define WIDTH 128
#define HEIGHT 64

#define GND_ROW HEIGHT-1 - BACK_H
#define SKY_ROW 0

#define st(a) i*a
#define random (rand() % 16) - 8

enum state { jump = 2, run1 = 0, run2 = 1 };

class Screen 
{
public:
	static int crop;
	static int height;
	static int width; 
	static char ** buffer;

	Screen(int _height, int _width, char _buffer);

	static void display();
	static void pixel(int col, int row, char colour);
};

class Character
{
public:
	int col;
	int row;
	char* bmp;
	state cond;
	int height;
	int width;

	Character(int _col, int _row, char* _bmp);
	Character(int _col, int _row, char* _bmp, int _height, int _width);

	void print();
	Character &  clear();
	bool check_hit(Character &enemy);
};

class Back 
{
public:
	char* bmp;
	int row;
	int col = 0;
	int height ;
	int width ;

	Back(char* _bmp, int _row);
	Back(char* _bmp, int _row, int _height, int _width);

	Back & offset();
	void print();
};

void jump_handler(Character &dino, int keylog);
void jump_handler(Character &dino, int keylog, int gnd_height);

void screen_init();

// void display();



void printScore(int &score);
