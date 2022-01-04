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

#define getch() _getch()

#define clear_console "cls"

enum state { jump = 2, run1 = 0, run2 = 1, background = 3 };

using image = std::pair<char**,std::pair<int,int>*>; 

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
/*
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

void jump_handler(Character &dino, int keylog);
void jump_handler(Character &dino);

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
*/
class Sprite 
{
	const int height;
	const int width;
public:
	int col;
	int row;
	char** bmp;
	state cond;
	
	Sprite(int _col, int _row, image* _img, state _cond);

	Sprite & clear();
	Sprite & offset();

	bool check_hit(Sprite &enemy);

	void print();

	friend void jump_handler(Sprite &dino, int keylog);
	friend void jump_handler(Sprite &dino);
};

void jump_handler(Sprite &dino, int keylog);
void jump_handler(Sprite &dino);

image* makeTransparent(image* img);

image* fileToArray(std::string filename);