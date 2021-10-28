#include "conio.h"
#include <Windows.h>
#include "cstdlib"
#include "Sprites.h"
#include "Backs.h"
#include "mylib.h"
;



//void display_stm() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			oled.print << (char)((int)buffer[j][i] * 219);
//		}
//	}
//}


int main() {
//restart:
	optim();
	state position = run2;
	Character dino{ 10, 31, dino_bmp[position], position };
	Character cactus1{ 127 +  random, 31, enemy_bmp, run1 };
	Character cactus2{ 127 + 128 + random, 31, enemy_bmp, run1 };
	Back clouds{ sky, SKY_ROW };
	Back gnd{ ground, GND_ROW };
	bool button = false;
	short tick = 1;
	system("mode con cols=128 lines=64");
	jump_handler(dino, RESET);
	button = false;
restart:
	// int score = 0;
	while (!(dino.check_hit(cactus1) || dino.check_hit(cactus2))) {

		if (dino.row == 31 && tick == 6) dino.cond = state(!bool(dino.cond));
		
		if (dino.row != 31) dino.cond = jump;

		dino.bmp = dino_bmp[dino.cond];

		if (cactus1.col < -15) cactus1.col = 127 + random;

		if (cactus2.col < -15) cactus2.col = 127 + random;

		clear();

		// printScore(score);

		clouds.print();

		gnd.print();

		dino.print();

		cactus1.print();

		cactus2.print();

		

		display();

		if (_kbhit()) {
			_getch();
			button = true;
		}
		jump_handler(dino, int(button));
		button = false;

		gnd.offset();

		if (tick % 2 == 0) clouds.offset();
		// if (tick == 5) score++;
		if (tick == 6) tick = 1;
		else tick++;

//		if !(dino.check_hit(&cactus1) || dino.check_hit(&cactus2))
//			break;

		cactus1.col--;
		cactus2.col--;
//		cactus1.col--;
//		cactus2.col--;
		
		Sleep(4);
    	}

	dino.row = 31;
	cactus1.col = 127;
	cactus2.col = 127 + random + 64;
	jump_handler(dino, RESET);
	tick = 1;
	goto restart;

	//while (true) {
	//	clear();
	//	cactus.print();
	//	clouds.print();
	//	clouds.offset();
	//	display();
	//	_getch();
	//}
	//while (1) {
	//	for (int i = 127; i > 0 - IMG_SIZE; i--) {
	//		clear();
	//		cactus.col = i;
	//		cactus.print();
	//		display();
	//		Sleep(5);
	//
	//	}
	//}
	//while (1) {
		//if (_kbhit()) {
		//	_getch();
		//	button = true;
		//}
		//jump_handler(&dino, button);
		//button = false;
	//	dino.print();
	//	display();
	//	clear();
	//	Sleep(10);
	//}
	//
		//int x = 0;
		//clear();
		//dino.print();
		//display();
		//_getch();
	//
		//while (!_kbhit()) {
		//	print_sprite(10, 10, dino_bmp[0]);
		//	x = int(!bool(x));
		//	display();
		//}
		////if (dino.row > START_DINO) position = jump;
		////else position = state(!bool(position));
		//display();
		//++tick;
//		system("cls");
	//	display();
//	
//	}

	
	}