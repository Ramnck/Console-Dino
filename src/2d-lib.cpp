#include<2d-lib.h>
#include<iostream>
;
//enum state { jump = 0, run1, run2 };

static char buffer[WIDTH * HEIGHT + 1];

// score = 0;

void optim() {
	std::ios::sync_with_stdio(false);
}

void pixel(int col, int row, bool colour) {
	if(colour)
	buffer[col + WIDTH * row] = 219;
}

//void print_sprite(int col, int row, bool sprite[]) {
//	for (int i = row; i < row + IMG_SIZE; i++) {
//		for (int j = col; j < col + IMG_SIZE; j++) {
//			pixel(j, i, sprite[j - col + (i - row) * IMG_SIZE]);
//		}
//	}
//
//}
//
//void print_back() {
//	int a = 1;
//
//}

void display() {
	buffer[WIDTH * HEIGHT] = '\0';
	std::cout << buffer << "\r";
}

void clear() {
	for (int i = 0; i < HEIGHT * WIDTH; i++)
		buffer[i] = ' ';
}

void jump_handler(Character &dino, int keylog) {
	static int tick = 0;
	static bool direction = UP;
	
	if (keylog == -1) {
		tick = 0;
		direction = UP;
		// score = 0;
		return;
	}

	if (tick == 0) tick = keylog;

	switch (tick)
	{
	case 1:
		dino.row = direction ? dino.row - 5 : dino.row + 5;
		tick = direction ? ++tick : --tick;
		direction = UP;
		break;
	case 2:
		dino.row = direction ? dino.row - 5 : dino.row + 5;
		tick = direction ? ++tick : --tick;
		break;
	case 3:
		tick = direction ? ++tick : --tick;
		break;
	case 4:
		dino.row = direction ? dino.row - 4 : dino.row + 4;
		tick = direction ? ++tick : --tick;
		break;
	case 5:
		tick = direction ? ++tick : --tick;
		break;
	case 6:
		dino.row = direction ? dino.row - 4 : dino.row + 4;
		tick = direction ? ++tick : --tick;
		break;
	case 7:
		tick = direction ? ++tick : --tick;
		break;
	case 8:
		tick = direction ? ++tick : --tick;
		break;
	case 9:
		dino.row = direction ? dino.row - 3: dino.row + 3;
		tick = direction ? ++ tick : -- tick;
		break;
	case 10:
		tick = direction ? ++tick : --tick;
		break;
	case 11:
		dino.row = direction ? dino.row - 3 : dino.row + 3;
		tick = direction ? ++ tick : -- tick;
		break;
	case 12:
		tick = direction ? ++tick : --tick;
		break;
	case 13:
		tick = direction ? ++tick : --tick;
		break;
	case 14:
		dino.row = direction ? dino.row - 2 : dino.row + 2;
		tick = direction ? ++ tick : -- tick;
		break;
	case 15:
		tick = direction ? ++tick : --tick;
		break;
	case 16:
		dino.row = direction ? dino.row - 1 : dino.row + 1;
		tick = direction ? ++tick : --tick;
		break;
	case 17:
		tick = direction ? ++tick : --tick;
		break;
	case 18:
		dino.row = direction ? dino.row - 1 : dino.row + 1;
		tick = direction ? ++tick : --tick;
		break;
	case 19:
		tick = direction ? ++tick : --tick;
		break;
	case 20:
		dino.row = direction ? dino.row - 1 : dino.row + 1;
		tick = direction ? ++tick : --tick;
		break;
	case 21:
		tick = direction ? ++tick : --tick;
		break;
	case 22:
		tick = direction ? ++tick : --tick;
		break;
	case 23:
		tick = direction ? ++tick : --tick;
		break;
	case 24:
		tick = direction ? ++tick : --tick;
		break;
	case 25:
		tick = direction ? ++tick : --tick;
		break;
	case 26:
		direction = DOWN;
		tick--;
		break;

	default:
		break;
	}

}

void printScore(int &score) {
	static bool cond = false;
	sprintf(buffer + WIDTH * 17 - 10, "%010d", score);
	buffer[WIDTH * 17] = ' ';
	// if (cond) 
		// score++;
	// cond = !cond;
}


void Character::print() {
	int l_offset = 0;
	int r_offset = 0;
	if (col > 127) return;

	if (col < 0) l_offset = 0 - col;

	if (col >= WIDTH - 1 - IMG_W) r_offset = IMG_W - (WIDTH - col);			// -1 ��� ��� ��������� ���������� � ���� 

	for (int i = row; i < row + IMG_H; i++) {
		for (int j = col + l_offset; j < col + IMG_W - r_offset; j++) {
			pixel(j, i, *(bmp + j - col + (i - row) * IMG_W));
		}
	}
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

void Back::offset() {
	for (int i = 0; i < BACK_H; i++) {
		bool left_reserved = *(bmp + st(WIDTH));
		for (int j = st(WIDTH); j < st(WIDTH) + WIDTH - 1; j++) {
			*(bmp + j) = *(bmp + j + 1);
		}
		*(bmp + WIDTH - 1 + WIDTH * i) = left_reserved;
	}
}

void Back::print() {
	int col = 0;
	for (int i = row; i < row + BACK_H; i++) {
		for (int j = col; j < col + 128; j++) {
			pixel(j, i, *(bmp + j - col + (i - row) * WIDTH));
		}
	}
}


/*
void offset_sky() {
	for (int i = 0; i < 28; i++) {
		bool left_reserved = sky[st(28) - 1];
		for (int j = st(28); j < st(28) + WIDTH - 1; j++) {
			sky[j] = ground[j + 1];
		}
		sky[WIDTH - 1 + WIDTH * i] = left_reserved;
	}

}

void offset_ground() {
	for (int i = 2; i < 28; i++) {
		bool left_reserved = ground[st(28) - 1];
		for (int j = st(28); j < st(28) + WIDTH - 1; j++) {
			ground[j] = ground[j + 1];
		}
		ground[WIDTH - 1 + WIDTH * i] = left_reserved;
	}


}
*/
