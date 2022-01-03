#include<2d-lib.h>

//enum state { jump = 0, run1, run2 };

// static char buffer[HEIGHT][WIDTH + 1];

// score = 0;

void Screen::init() {
	// std::cout << "starting Screen init\n";
	// std::cout << "external schecking width: " << Screen::width << " height " << Screen::height << " buf: " << Screen::buffer << "\n";
	std::ios::sync_with_stdio(false);
	// std::cout << "syncing over\n";
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	
	// std::cout << "setvbuffing over\n";
	for (int i = 0; i < Screen::height; i++) {
		// std::cout << i << '\n';
		Screen::buffer[i][Screen::width] = '\0';
		memset(Screen::buffer[i], ' ', Screen::width);
	}
	// std::cout << "ending Screen init\n";
	#ifdef WIN32
	system("mode con cols=128 lines=65");
	#endif
	system(clear_console);
}
/*
Screen::Screen(int _height, int _width, char** _buffer) {
	heigth = _height;
	width = _width;
	buffer = _buffer;
}
*/

void Screen::pixel(int col, int row, char colour) {
	if(colour != ' ') 
		buffer[row][col] = -37;
	else 
		buffer[row][col] = ' ';
}

void Screen::display() {
	// system(clear_console);

	for(int i = 0; i < Screen::height + 1; i++)
		puts(buffer[i]);
}

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

/*
void printScore(int &score) {
	char tick = 0;
	sprintf(Screen::buffer[17] - 10, "%5d", score);
	// buffer[WIDTH * 17] = ' ';
	// if (!(tick = (++tick) % 3)) 
		score++;
}
*/

Character::Character(int _col, int _row, char* _bmp) : col(_col), row(_row), bmp(_bmp), cond(run1), height(IMG_H), width(IMG_W) {}

Character::Character(int _col, int _row, char* _bmp, int _height, int _width) : col(_col), row(_row), bmp(_bmp), cond(run1), height(_height), width(_width) {}

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
	// */
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
/*
	for(int i = row; i < row + BACK_H; i++) {
		char left_reserved = buffer[i][0];
		memcpy(buffer[i], buffer[i] + 1, WIDTH - 1);
		buffer[i][WIDTH - 1] = left_reserved;
	}
*/
/*
	for (int i = 0; i < BACK_H; i++) {
		bool left_reserved = *(bmp + st(WIDTH));
		for (int j = st(WIDTH); j < st(WIDTH) + WIDTH - 1; j++) {
			*(bmp + j) = *(bmp + j + 1);
		}
		*(bmp + WIDTH - 1 + WIDTH * i) = left_reserved;
	}
*/
}

void Back::print() {

	// for (int i = row; i < row + height; i++) {
	// 	for (int j = col; j < col + width; j++) {
	// 		Screen::pixel(j, i, *(bmp + j - col + (i - row) * Screen::width));
	// 	}
	// }
	for (int h = 0; h < height; h++) memcpy(Screen::buffer[h + row], bmp + (width * h), width);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


Sprite::Sprite(int _col, int _row, char** _bmp, int _height, int _width, state _cond) :
	col(_col), row(_row), bmp(bmp), height(_height), width(_width), cond(_cond) {}


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
		/*
		char cur_pixel;
		for (int i = row; i < row + height; i++) {
			for (int j = col + l_offset; j < col + width - r_offset; j++) {
				cur_pixel = *(bmp + j - col + (i - row) * width);
				if (cur_pixel == -37)
					Screen::pixel(j, i, -37);
			}
		}
		*/
		for (int h = 0; h < height; h++) 
			for (int w = l_offset; w < width - r_offset; w++) 
				if (bmp[h][w] == -37)
					Screen::pixel(w + col, h + row, -37);
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
	if (col > (Screen::width - 1)) return;
	if (col < 0) l_offset = 0 - col;
	if (col >= Screen::width - 1 - width) r_offset = width - (Screen::width - col);
	/*
	char cur_pixel;
	for (int i = row; i < row + height; i++) {
		for (int j = col + l_offset; j < col + width - r_offset; j++) {
			cur_pixel = *(bmp + j - col + (i - row) * width);
			if (cur_pixel == -37)
				Screen::pixel(j, i, ' ');
		}
	}
	*/
	for (int h = 0; h < height; h++) 
		for (int w = l_offset; w < width - r_offset; w++) 
			if (bmp[h][w] == -37)
				Screen::pixel(w + col, h + row, ' ');
	return *this;
}

bool Sprite::check_hit(Sprite &enemy) {
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