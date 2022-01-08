#pragma once

#include <other/global.hpp>

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