#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <conio.h>

#define RESET -1
#define random (rand() % 9) - 4

#define IMG_H 16
#define IMG_W 16
#define BACK_H 16

#define WIDTH 128
#define HEIGHT 64

#define GND_ROW HEIGHT-1 - BACK_H
#define SKY_ROW 0

#ifdef WIN32
#define getch() _getch()
#endif

#ifdef WIN32
#define clear_console "cls"
#else
#define clear_console "clear"
#endif

enum state { jump = 2, run1 = 0, run2 = 1, background = 3 };

class Screen 
{
public:
	static int scale;
	static int height;
	static int width; 
	static char ** buffer;
	static int jump_tick;
	static int dino_default_row;

	Screen(int _height, int _width, char _buffer);

	static void init();
	static void display();
	static void pixel(int col, int row, char colour);
};

class Character
{
public:
	int col;
	int row;
	char* bmp;
	int height;
	int width;
	state cond;
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

class Sprite 
{
public:
	int col;
	int row;
	char* bmp;
	int height;
	int width;
	state cond;

	Sprite(int _col, int _row, char* _bmp, int _height, int _width);

	Sprite & clear();
	Sprite & offset();

	bool check_hit(Character &enemy);

	void print();

	friend void jump_handler(Character &dino, int keylog);
	friend void jump_handler(Character &dino);
};

void jump_handler(Character &dino, int keylog);
void jump_handler(Character &dino);

// void printScore(int &score);
