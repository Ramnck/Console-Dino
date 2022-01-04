#include<2d-lib.h>

void Screen::init() {

	std::ios::sync_with_stdio(false);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	
	for (int i = 0; i < Screen::height; i++) {
		// std::cout << i << '\n';
		Screen::buffer[i][Screen::width] = '\0';
		memset(Screen::buffer[i], ' ', Screen::width);
	}
	system("mode con cols=128 lines=65");
	system(clear_console);
}

void Screen::pixel(int col, int row, char colour) {
	if (colour == 101) return;
	buffer[row][col] = colour;
}

void Screen::display() {
	for(int i = 0; i < Screen::height; i++) puts(buffer[i]);
}


std::pair<int, int>* resolution(std::string filename) {
    FILE * file = fopen(filename.c_str(), "rb");
    int width, height;
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fclose(file);
    std::pair<int, int>* ptr = new std::pair<int, int>;
    *ptr = std::make_pair(width, height);
    return ptr;
}

image* fileToArray(std::string filename) {
    FILE * file = fopen(filename.c_str(), "rb");
    short d;
    fseek(file, 18, SEEK_SET);
    int width, height;
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fseek(file, 28, SEEK_SET);
    fread(&d, 2, 1, file);
    if (d != 1) { printf("\nERROR: wrong color depth in file %s\n",filename); exit(1); }
    // cout << width << ' ' << height << ' ' << d << '\n';
    // char array[height][width];

    char** array = new char*[height]; for(int i = 0; i < height; i++) array[i] = new char[width];

    fseek(file, 62, SEEK_SET);
    for (int h = height - 1; h >= 0; h--) {
        char byte, bits_left, bytes_to_skip = (4 - ((int)std::ceil( (double)width / 8.0 ) % 4)) % 4;
        bits_left = width;
        while (bits_left > 0) {
            fread(&byte, 1, 1, file);
            int x = 8 - std::min(8, (int)bits_left);
            for(int bit_mask = std::pow(2,7); bit_mask >= std::pow(2, x); bit_mask /= 2)
                array[h][width - bits_left--] = byte & bit_mask ? ' ' : -37;
        }
        fseek(file, bytes_to_skip, SEEK_CUR);
    }
    fclose(file);

	image* output = new image; output->second = new std::pair<int,int>;
	output->first = array; output->first = width; output->second = height;

    return output;
}

image* makeTransparent(image* img) {
	for (int h = 0; h < img->second->second; h++)
		for(int w = 0; w < img->second->first; w++)
			if (img->first[h][w] == ' ') img->first[h][w] = 101;
	return img;
}

/*
void jump_handler(Character &dino, int keylog) {

	if (Screen::jump_tick == 0) Screen::jump_tick = keylog;
	else Screen::jump_tick = ((Screen::jump_tick + 1) * Screen::scale) % 62;

	dino.row = std::max(std::min((int)round(0.037 * (Screen::jump_tick-31) * (Screen::jump_tick-31) - 1.5), 31), 2) / Screen::scale;
}

void jump_handler(Character &dino) {
	Screen::jump_tick = 0;
	dino.row = Screen::dino_default_row;
	return;
}



Character::Character(int _col, int _row, char* _bmp) : col(_col), row(_row), bmp(_bmp), cond(run1), height(IMG_H), width(IMG_W) {}

Character::Character(int _col, int _row, char* _bmp, int _height, int _width) : 
	col(_col), row(_row), bmp(_bmp), 
	cond(run1), height(_height), width(_width) {}

void Character::print() {
	int l_offset = 0;
	int r_offset = 0;
	if (col > (Screen::width - 1)) return;
	if (col < 0) l_offset = 0 - col;
	if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
	
	char cur_pixel;
	for (int i = row; i < row + height; i++) {
		for (int j = col + l_offset; j < col + width - r_offset; j++) {
			cur_pixel = *(bmp + j - col + (i - row) * width);
			if (cur_pixel == -37)
				Screen::pixel(j, i, -37);
		}
	}

}

Character & Character::clear() {
	int l_offset = 0;
	int r_offset = 0;
	if (col > (Screen::width - 1)) return *this;
	if (col < 0) l_offset = 0 - col;
	if (col >= Screen::width - 1 - height) r_offset = height - (Screen::width - col);
	char cur_pixel;
	for (int i = row; i < row + height; i++) {
		for (int j = col + l_offset; j < col + width - r_offset; j++) {
			cur_pixel = *(bmp + j - col + (i - row) * width);
			if (cur_pixel == -37)
				Screen::pixel(j, i, ' ');
		}
	}
	return *this;
}

bool Character::check_hit(Character &enemy) {							// enemy is cactus
	if ((row + height) / 4 * 3  < enemy.row) {
		return false;
	}
	else {
		if (col + height < enemy.col || col > enemy.col + enemy.width) 
			return false;
		else
			return true;
	}
}

Back::Back(char* _bmp, int _row) : bmp(_bmp), row(_row), height(BACK_H), width(Screen::width) {}

Back::Back(char* _bmp, int _row, int _height, int _width) : bmp(_bmp), row(_row), height(_height), width(_width) {}

Back & Back::offset() {
	for(int i = 0; i < height * Screen::width; i+= Screen::width) {
		char left_reserved = bmp[i];
		memcpy(bmp + i, bmp + i + 1, Screen::width - 1);
		bmp[i - 1 + Screen::width] = left_reserved;
	}
	return *this;

}

void Back::print() {
	for (int h = 0; h < height; h++) memcpy(Screen::buffer[h + row], bmp + (width * h), width);
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


Sprite::Sprite(int _col, int _row, image* _img, state _cond = run1) :
	col(_col), row(_row), bmp(_img->first), 
	height(_img->second->second), width(_img->second->first), cond(_cond) {}


void Sprite::print() {

	switch (cond)
	{
	case background:
		for (int h = 0; h < height; h++) memcpy(Screen::buffer[h + row] + col, bmp + (width * h), width);
		break;

	default:
		int l_offset = 0, r_offset = 0;
		if (col > (Screen::width - 1)) return;
		if (col < 0) l_offset = 0 - col;
		if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
		
		for (int h = 0; h < height; h++) 
			for (int w = l_offset; w < width - r_offset; w++) 
				Screen::pixel(w + col, h + row, bmp[h][w]);
		break;
	
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
	int l_offset = 0, r_offset = 0;
	
	if (col > (Screen::width - 1)) return *this;
	if (col < 0) l_offset = 0 - col;
	if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
	
	for (int h = 0; h < height; h++) 
		for (int w = l_offset; w < width - r_offset; w++) 
			Screen::pixel(w + col, h + row, bmp[h][w] + 69);
	
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