
// #ifdef WIN32
// #include <Windows.h>
// #else

// #endif
#include <Sprites.h>
#include <Backs.h>
#include <2d-lib.h>

#define FPS 2.0
;



//void display_stm() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			oled.print << (char)((int)buffer[j][i] * 219);
//		}
//	}
//}


int main(int argc, char* argv[]) {
//restart:
	screen_init();

	#ifdef FPS
	double FRQ;
	if (argc > 1)
		FRQ = 1.0/std::stoi(argv[1]);
	else
		FRQ = 1.0/FPS;
	std::clock_t start;
	#endif
	
	state position = run2;

	Character dino{ 10, 31, dino_bmp[position], position };
	Character cactus1{ 127 +  random, 31, enemy_bmp, run1 };
	Character cactus2{ 127 + 128 + random, 31, enemy_bmp, run1 };

	Back clouds{ sky, SKY_ROW };
	Back gnd{ ground, GND_ROW };
	
	bool button = false;
	short tick = 1;
	jump_handler(dino, RESET);
    
	clouds.print();
	gnd.print();

restart:
	// int score = 0;
	while (!(dino.check_hit(cactus1) || dino.check_hit(cactus2))) {
		#ifdef FPS
		start = std::clock();
		#endif
		if (dino.row == 31 && tick == 6) dino.cond = state(!bool(dino.cond));
		
		if (dino.row != 31) dino.cond = jump;

		dino.bmp = dino_bmp[dino.cond];

		if (cactus1.col < -15) cactus1.col = 127 + random;

		if (cactus2.col < -15) cactus2.col = 127 + random;

		// printScore(score);

		// clouds.print();

		// gnd.print();

		dino.print();

		cactus1.print();

		cactus2.print();

		display();
		#ifdef WIN32
		if (_kbhit()) {
			_getch();
			button = true;
		}
		#else
		if (kbhit()) {
			getch();
			button = true;
		}
		#endif
		jump_handler(dino, int(button));
		button = false;

		gnd.offset();

		if (tick % 2 == 0) clouds.offset();
		// if (tick == 5) score++;
		if (tick == 6) tick = 1;
		else tick++;

		// if (!(dino.check_hit(&cactus1)) || dino.check_hit(&cactus2))
			// break;

		cactus1.col--;
		cactus2.col--;

		#ifdef FPS
		while (( std::clock() - start ) / (double) CLOCKS_PER_SEC < FRQ)
			usleep(300);
		#endif

    	}
	
	// std::cout << duration << std::endl;
	dino.row = 31;
	cactus1.col = 127;
	cactus2.col = 127 + random + 64;
	jump_handler(dino, RESET);
	tick = 1;
	// goto restart;
	}