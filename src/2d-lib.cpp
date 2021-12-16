#include<2d-lib.h>
;
//enum state { jump = 0, run1, run2 };

static char buffer[HEIGHT][WIDTH + 1];

#ifdef WIN32
char clear_console[] = "cls";
#else
char clear_console[] = "clear";
#endif

// score = 0;

void screen_init() {
	std::ios::sync_with_stdio(false);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	for (int i = 0; i < HEIGHT; i++) {
		buffer[i][128] = '\0';
		memset(buffer[i], ' ', WIDTH);
	}
	#ifdef WIN32
	system("mode con cols=128 lines=64");
	#endif
}

void pixel(int col, int row, char colour) {
	if(colour != ' ') 
		buffer[row][col] = -37;
	else 
		buffer[row][col] = ' ';
}

void display() {
	// system(clear_console);

	for(int i = 0; i < HEIGHT + 1; i++)
		puts(buffer[i]);
}

void jump_handler(Character &dino, int keylog) {
	static int tick = 0;
	// static bool direction = UP;
	
	if (keylog == -1) {
		tick = 0;
		// direction = UP;
		dino.row = 31;
		// score = 0;
		return;
	}

	if (tick == 0) tick = keylog;
	// if (tick == 0) tick = 1;
	else tick = (++tick) % 62;

	dino.row = std::max(std::min((int)round(0.037 * (tick-31) * (tick-31) - 1.5), 31), 2);
	}

// /*
void printScore(int &score) {
	char tick = 0;
	sprintf(buffer[17] - 10, "%5d", score);
	// buffer[WIDTH * 17] = ' ';
	// if (!(tick = (++tick) % 3)) 
		score++;
}
// */

void Character::print() {
	int l_offset = 0;
	int r_offset = 0;
	if (col > 127) return;
	if (col < 0) l_offset = 0 - col;
	if (col >= WIDTH - 1 - IMG_W) r_offset = IMG_W - (WIDTH - col);			// -1 ��� ��� ��������� ���������� � ���� 
	/*
	for (int i = 0; i < IMG_W; i++){
		// memset(&buffer[row + i][col + l_offset], ' ', IMG_W - l_offset - r_offset);
		memcpy(buffer[row + i] + col + l_offset, bmp+ (row + i) * IMG_W + l_offset , IMG_W - l_offset - r_offset);
	}
	*/
	// /*
	
	
	char cur_pixel;
	for (int i = row; i < row + IMG_H; i++) {
		for (int j = col + l_offset; j < col + IMG_W - r_offset; j++) {
			cur_pixel = *(bmp + j - col + (i - row) * IMG_W);
			if (cur_pixel == -37)
				pixel(j, i, -37);
		}
	}
	// */
}

Character & Character::clear() {
	int l_offset = 0;
	int r_offset = 0;
	if (col > 127) return *this;
	if (col < 0) l_offset = 0 - col;
	if (col >= WIDTH - 1 - IMG_W) r_offset = IMG_W - (WIDTH - col);
	char cur_pixel;
	for (int i = row; i < row + IMG_H; i++) {
		for (int j = col + l_offset; j < col + IMG_W - r_offset; j++) {
			cur_pixel = *(bmp + j - col + (i - row) * IMG_W);
			if (cur_pixel == -37)
				pixel(j, i, ' ');
		}
	}
	return *this;
}

bool Character::check_hit(Character &enemy) {							// enemy is cactus
	if (row + IMG_H - 5 < enemy.row) {								// -3 ������ ��� ������ �������� ����������� ���� ������ ��� ������ �������
		return false;
	}
	else {
		if (col + IMG_W < enemy.col || col > enemy.col + IMG_W) {
			return false;
		}
		else {
			return true;
		}
	}
}

Back & Back::offset() {
	for(int i = 0; i < BACK_H * WIDTH; i+= WIDTH) {
		char left_reserved = bmp[i];
		memcpy(bmp + i, bmp + i + 1, WIDTH - 1);
		bmp[i - 1 + WIDTH] = left_reserved;
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
	int col = 0;
	for (int i = row; i < row + BACK_H; i++) {
		for (int j = col; j < col + 128; j++) {
			pixel(j, i, *(bmp + j - col + (i - row) * WIDTH));
		}
	}
}
