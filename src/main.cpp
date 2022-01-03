#include <Sprites.h>
#include <Backs.h>
#include <2d-lib.h>
#include <string>
#define FPS 120.0

// initializating global variables
int Screen::scale;
int Screen::height;
int Screen::width;
char** Screen::buffer;
int Screen::jump_tick;
int Screen::dino_default_row;

int main(int argc, char* argv[]) {

	// int _s = 0;

	// Handling console arguments
	#ifdef FPS
	double FRQ = 1.0/FPS;
	std::clock_t start;
	if (argc > 1) {
		std::string flag (argv[1]), num;
		if (argc > 2) 
			num = argv[2];
		if (flag == "-h" || flag == "--help") {
			// printf("Usage: %s [-h | --help] [-s to print score] [-f | --fps <FPS> (default = 30)] ", argv[0]);
			printf("Usage: %s [-h | --help] [-f | --fps <FPS> (default = 30)] ", argv[0]);
			exit(1);
		}
		/*
		if (flag == "-s") {
			_s = 1;
			if (argc > 2) {
				flag = argv[2];
				num = argv[3];
			}
		}
		*/
		if (flag == "-f" || flag == "--fps")
			FRQ = 1.0/double(std::stoi(num.c_str()));
	}
	#endif
	printf("%f", FRQ);
	// screen and game variables
	int height = 64, width = 128, scale = 1, button = 0, tick = 1;

	// Allocating screen buffer;
	char** buffer = new char*[height];
	for (int i = 0; i < height; i++)
		buffer[i] = new char[width + 1];

	// Screen initialization
	Screen::scale = scale;
	Screen::height = height;
	Screen::width = width;
	Screen::buffer = (char**)buffer;
	Screen::init();

	// Backs initialization
	Back clouds(sky, SKY_ROW);
	Back gnd(ground, GND_ROW);

	// Characters initialization
	Character dino( Screen::width / 12, 0, dino_bmp[0] );
	Character cactus1( Screen::width +  random, Screen::height - gnd.height - IMG_H - 1, enemy_bmp );
	Character cactus2( (Screen::width * 2) + random, Screen::height - gnd.height - IMG_H - 1, enemy_bmp );
	Screen::dino_default_row = Screen::height - 1 - dino.height - gnd.height;

restart:
	jump_handler(dino);
	// int score = _s;
	while (!(dino.check_hit(cactus1) || dino.check_hit(cactus2))) {

		#ifdef FPS
		start = std::clock();
		#endif

		tick = (tick + 1) % 7;

		// Changing dino's sprite 
		if (dino.row == Screen::dino_default_row && tick == 6) dino.cond = state(!bool(dino.cond));
		else if (dino.row < Screen::dino_default_row) dino.cond = jump;
		else if (dino.row > Screen::dino_default_row) {
			printf("ERROR: Character row %d", dino.row);
			exit(1);
		}
		dino.bmp = dino_bmp[dino.cond];

		// Respawning cactuses
		if (cactus1.col < -cactus1.width + 1) cactus1.col = Screen::width + random;
		if (cactus2.col < -cactus2.width + 1) cactus2.col = Screen::width + random;

		/*
		if (score)
			printScore(score);
		*/

		// Printing and ofsetting backs
		if (tick % 3 == 0) 
			clouds.offset();
		clouds.print();
		gnd.offset().print();

		// Printing characters
		dino.print();
		cactus1.print();
		cactus2.print();

		// Displaying buffer
		Screen::display();
		
		// Jump handling
		if (_kbhit()) 
			if (getch() == 32) // Space
				button = 1;
		jump_handler(dino.clear(), button);
		button = 0;

		// Moving cactuses
		cactus1.clear().col--;
		cactus2.clear().col--;

		// Framerate control
		#ifdef FPS
		while ((( std::clock() - start ) / (double) CLOCKS_PER_SEC) < FRQ);
		#endif

    	}
	
	// Resetting all values
	cactus1.col = Screen::width;
	cactus2.col = Screen::width + random + (Screen::width / 2);
	jump_handler(dino, RESET);
	tick = 1;
	system(clear_console);
	
	// End message
	printf("Haha you losed (Click any key to continue)\nESC to exit\n");
	if (_getch() == 27) {
		printf("Thanks for playing");
		return 0;
	}
	std::cin.clear();
	
	// Restart
	goto restart;
	return 0;
}