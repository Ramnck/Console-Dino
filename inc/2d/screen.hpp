#pragma once

#include <other/global.hpp>

class Screen 
{
public:
	static int scale;
	static int height;
	static int width; 
	static char * buffer;
	static int jump_tick;
	static int dino_default_row;
	static HANDLE console_handler;
	static DWORD bytes_written;

	Screen(int _height, int _width, char _buffer);

	static void fill();
	static void clear();
	static void init(int width, int height);
	static void display();
	static void pixel(int col, int row, char colour);
};