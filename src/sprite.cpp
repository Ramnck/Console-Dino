#include<2d/screen.hpp>
#include<2d/sprite.hpp>

void jump_handler(Sprite &dino, int keylog) {

	if (Screen::jump_tick == 0) Screen::jump_tick = keylog;
	else Screen::jump_tick = ((Screen::jump_tick + 1) * Screen::scale) % 62;

	dino.row = std::max(std::min((int)round(0.037 * (Screen::jump_tick-31) * (Screen::jump_tick-31) - 1.5) - (dino.height - 16), 31), 2) / Screen::scale;
}

void jump_handler(Sprite &dino) {
	Screen::jump_tick = 0;
	dino.row = Screen::dino_default_row;
	return;
}

Sprite::Sprite(int _col, int _row, image* _img, state _kind) :
	col(_col), row(_row), bmp(_img->first), 
	height(_img->second->second), width(_img->second->first), kind(_kind) {}

std::pair<int,int> Sprite::getResolution() { return std::make_pair(width,height); }

void Sprite::print() {

	if (kind == character) {
		for (int h = 0; h < height; h++) 
			for (int w = 0; w < width ; w++) 
				if (bmp[h][w] == -37)
					Screen::pixel(w + col, h + row, -37);
	}

	else if (kind == enemy) {
		int l_offset = 0, r_offset = 0;
		if (col > (Screen::width - 1)) return;
		else if (col < 0) l_offset = 0 - col;
		else if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
		
		for (int h = 0; h < height; h++)
			memcpy(Screen::buffer + ((h + row) * Screen::width) + col + l_offset, bmp[h] + l_offset, width - l_offset - r_offset);
	}

	else if (kind == background) {
		for (int h = 0; h < height; h++)
			memcpy(Screen::buffer + ((h + row) * Screen::width) + col, bmp[h], width);
	}
}

Sprite & Sprite::offset() {
	for(int i = 0; i < height; i++) {
		char left_reserved = bmp[i][0];
		memcpy(bmp[i], bmp[i] + 1, width - 1);
		bmp[i][width - 1] = left_reserved;
	}
	return *this;
}

Sprite & Sprite::clear() {
	if(kind == enemy) {
	int l_offset = 0, r_offset = 0;
	
	if (col > (Screen::width - 1)) return *this;
	else if (col < 0) l_offset = 0 - col;
	else if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
	
	for (int h = 0; h < height; h++) 
		for (int w = l_offset; w < width - r_offset; w++) 
			memset(Screen::buffer + ((h + row) * Screen::width) + col + l_offset, ' ', width - l_offset - r_offset);
	}
	else if (kind == character) {
		for (int h = 0; h < height; h++) 
			for (int w = 0; w < width; w++) 
				if (bmp[h][w] == -37)
					Screen::pixel(w + col, h + row, ' ');
	}
	return *this;
}

bool Sprite::check_hit(Sprite &enemy) {
	if (((row + height) / 4 * 3  < enemy.row) || ((enemy.row + enemy.height) / 4 * 3  < row)) {
		return false;
	}
	else {
		if (col + height < enemy.col || col > enemy.col + enemy.width) return false;
		else return true;
	}
}

void Sprite::test() { print(); Screen::display(); printf("%d %d %d %d \n", height, width, col, row);}

void testImage(char ** bmp, std::pair<int,int> resolution) {
	// system("cls");
	for (int h = 0; h < resolution.second; h++){
		for (int w = 0; w < resolution.first; w++) 
			printf("%c", bmp[h][w]);
		printf("\n");
	}
}