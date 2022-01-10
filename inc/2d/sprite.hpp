#pragma once

#include <other/global.hpp>

#define RESET -1

#define getch() _getch()

enum state { character, background, enemy };

// using image = std::pair<char**,std::pair<int,int>*>; 

struct image {
	char** bmp;
	int w;
	int h;
	~image();
};

class Sprite 
{
	const int height;
	const int width;
	const state kind;
public:
	int col;
	int row;
	char** bmp;
	
	
	Sprite(int _col, int _row, image* _img, state _kind);

	std::pair<int,int> getResolution();

	Sprite & clear();
	Sprite & offset();

	bool check_hit(Sprite &enemy);

	void print();

	void test();

	friend void jump_handler(Sprite &dino, int keylog);
	friend void jump_handler(Sprite &dino);
};

void jump_handler(Sprite &dino, int keylog);
void jump_handler(Sprite &dino);

void testImage(char ** bmp, std::pair<int,int> resolution);

image* fileToArray(std::string filename);

image* crop(image* img);