#include <2d/screen.hpp>
#include <2d/sprite.hpp>
#define FPS 120.0

// initializating global variables
int Screen::scale;
int Screen::height;
int Screen::width;
char* Screen::buffer;
int Screen::jump_tick;
int Screen::dino_default_row;

int main(int argc, char* argv[]) {
	
	// Handling console arguments
	double FRQ = 1.0/60;
	std::clock_t start;
	if (argc > 1) {
		std::string flag (argv[1]), num;
		if (argc > 2) num = argv[2];
		if (flag == "-h" || flag == "--help") {
			printf("Usage: %s [-h | --help] [-f | --fps <FPS> (default = 60)] ", argv[0]);
			return 0;
		}
		if (flag == "-f" || flag == "--fps") FRQ = 1.0/double(std::stoi(num.c_str()));
	}

	// printf("FRQ is %f, argc is %d", FRQ, argc); _getch();

	// screen and game variables
	int height = 64, width = 128, scale = 1, button = 0, tick = 1;

	// Allocating screen buffer;
	// char** buffer = new char*[height]; for (int i = 0; i < height; i++) buffer[i] = new char[width + 1];
	char* buffer = new char[height*width];
	// Screen initialization
	Screen::scale = scale;
	Screen::height = height;
	Screen::width = width;
	Screen::buffer = buffer;
	Screen::init();


	/*
	// Backs initialization
	Back clouds(sky, SKY_ROW);
	Back gnd(ground, GND_ROW);

	// Characters initialization
	Character dino( Screen::width / 12, 0, dino_bmp[0] );
	Character cactusk1( Screen::width + random, Screen::height - gnd.height - IMG_H - 1, enemy_bmp );
	Character cactusk2( (Screen::width * 1.5) + random, Screen::height - gnd.height - IMG_H - 1, enemy_bmp );
	*/

	Sprite clouds(0, 0, fileToArray("res/clouds.bmp"), background);
	
	image* gnd_img = fileToArray("res/ground.bmp");
	Sprite gnd (0, Screen::height - 1 - gnd_img->second->second, gnd_img, background);

	// printf("backs is initializated\n");

	char** dino_bmps[3] = {fileToArray("res/run1.bmp")->first, fileToArray("res/run2.bmp")->first, fileToArray("res/jump.bmp")->first};

	// printf("array is initializated\n"); 

	Sprite dino (Screen::width / 12, 0, fileToArray("res/run1.bmp"), character);
	Screen::dino_default_row = Screen::height - 1 - dino.getResolution().second - gnd_img->second->second;

	// printf("dino is initializated");

	Sprite cactusk1(Screen::width + random, Screen::dino_default_row, fileToArray("res/cactus.bmp"), enemy);
	Sprite cactusk2(Screen::width * 1.5 + random, Screen::dino_default_row, fileToArray("res/cactus.bmp"), enemy);

	// gnd.test(); getch();

	// testImage(clouds.bmp, clouds.getResolution()); getch();
	// testImage(gnd.bmp, gnd.getResolution()); getch();

	// testImage(cactusk1.bmp, cactusk1.getResolution()); getch();

	// testImage(dino_bmps[0], dino.getResolution()); getch();
	// testImage(dino_bmps[1], dino.getResolution()); getch();
	// testImage(dino_bmps[2], dino.getResolution()); getch();
	// printf("everybody is initializated"); getch();
restart:
	jump_handler(dino);
	while (!(dino.check_hit(cactusk1) || dino.check_hit(cactusk2))) {

		start = std::clock();

		tick = (tick + 1) % 13;


		if (dino.row == Screen::dino_default_row && !(tick % 6)) dino.bmp = dino_bmps[!(tick % 12)];
		else if (dino.row < Screen::dino_default_row) dino.bmp = dino_bmps[2];
		else if (dino.row > Screen::dino_default_row) { printf("ERROR: Character row %d", dino.row); return 1; } 

		/*
		// Changing dino's sprite 
		if (dino.row == Screen::dino_default_row && tick == 6) dino.cond = state(!bool(dino.cond));
		else if (dino.row < Screen::dino_default_row) dino.cond = jump;
		else if (dino.row > Screen::dino_default_row) {
			printf("ERROR: Character row %d", dino.row);
			return 1;
		}
		dino.bmp = dino_bmp[dino.cond];
		*/
		// Respawning cactuskes
		if (cactusk1.col < -cactusk1.getResolution().first + 1) cactusk1.col = Screen::width + random;
		if (cactusk2.col < -cactusk2.getResolution().first + 1) cactusk2.col = Screen::width + random;

		// Printing and ofsetting backs
		if (tick % 3 == 0) clouds.offset();
		clouds.print();
		gnd.offset().print();

		// Printing characters
		dino.print();
		cactusk1.print();
		cactusk2.print();

		// Displaying buffer
		Screen::display();

		// Jump handling
		if (_kbhit()) 
			if (getch() == 32) // Space
				button = 1;
		jump_handler(dino.clear(), button);
		button = 0;

		// Moving cactuskes
		cactusk1.clear().col--;
		cactusk2.clear().col--;

		// Framerate control

		while ((( std::clock() - start ) / (double) CLOCKS_PER_SEC) < FRQ);

    	}
	
	// Resetting all values
	cactusk1.col = Screen::width;
	cactusk2.col = Screen::width + random + (Screen::width / 2);
	jump_handler(dino, RESET);
	tick = 1;
	system("cls");
	
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