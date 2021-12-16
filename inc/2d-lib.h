#pragma once
;
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
#define random (rand() % 64)

enum state { jump = 2, run1 = 0, run2 = 1 };

class Character
{	
public:
	int col;
	int row;
	bool* bmp;
	state cond;

	void print();
	bool check_hit(Character &enemy);
};

class Back 
{
public:
	bool* bmp;
	int row;
	void offset();
	void print();
};

void jump_handler(Character &dino, int keylog);

void screen_init();

void display();

void pixel(int col, int row, bool colour);

void printScore(int &score);

/*
void print_sprite(int col, int row, bool sprite[]);

void print_back();

void offset_sky();

void offset_ground();

bool check_hit(int col, int row);
*/