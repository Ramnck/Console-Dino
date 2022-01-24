#include <2d/screen.hpp>
#include <2d/sprite.hpp>
#define FPS 60.0

// initializating global variables
int Screen::scale;
int Screen::height;
int Screen::width;
char* Screen::buffer;
int Screen::jump_tick;
int Screen::dino_default_row;
HANDLE Screen::console_handler;
DWORD Screen::bytes_written = 0;

int main(int argc, char* argv[]) {
	
	// Handling console arguments
	double FRQ = 1.0/FPS;
	std::clock_t start;
	
	// screen and game variables
	int height = 64, width = 128, scale = 1, button = 0, tick = 1;

	for(int i = 1; i < argc; i++) {
		if ((std::string) argv[i] == "-h" ) {printf("Usage: %s [-h | --help] [-f | --fps <FPS> (default = 60)] ", argv[0]); return 0;}
		else if ((std::string) argv[i] == "-f" || (std::string) argv[i] == "--fps") FRQ = 1.0/atoi(argv[i+1]);
	}

	// Screen initialization
	Screen::scale = scale;
	Screen::width = width;
	Screen::height = height;
	Screen::bytes_written = 0;
	Screen::init(width, height);

	Sprite clouds(0, 0, fileToArray("res/clouds.bmp"), background);
	
	image* gnd_img = fileToArray("res/ground.bmp");
	Sprite gnd (0, Screen::height - 1 - gnd_img->h, gnd_img, background);

	char** dino_bmps[3] = {fileToArray("res/run1.bmp")->bmp, fileToArray("res/run2.bmp")->bmp, fileToArray("res/jump.bmp")->bmp};

	Sprite dino (Screen::width / 12, 0, fileToArray("res/run1.bmp"), character);
	Screen::dino_default_row = Screen::height - 1 - dino.getResolution().second - gnd_img->h;

	Sprite cactusk1(width + random, 0, fileToArray("res/cactus.bmp"), enemy);
	cactusk1.row = height - 1 - cactusk1.getResolution().second - gnd_img->h;
	Sprite cactusk2(width * 1.5 + random, cactusk1.row, fileToArray("res/cactus.bmp"), enemy);
	cactusk2.row = height - 1 - cactusk2.getResolution().second - gnd_img->h;
	// testImage(fileToArray("res/run1.bmp"));
	{
	Sprite(0,0,fileToArray("res/startscreen.bmp"), background).print();
	Screen::display();
	if (_getch() == 27) { printf("Thanks for playing"); return 0; }
	}

restart:
	jump_handler(dino);
	Screen::clear();

	while (!(dino.check_hit(cactusk1) || dino.check_hit(cactusk2))) {

		start = std::clock();

		tick = (tick + 1) % 13;

		if (dino.row == Screen::dino_default_row && !(tick % 6)) dino.bmp = dino_bmps[!(tick % 12)];
		else if (dino.row < Screen::dino_default_row) dino.bmp = dino_bmps[2];
		else if (dino.row > Screen::dino_default_row) { printf("ERROR: character row %d", dino.row); return 1; } 

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
		if (_kbhit()) {
			switch (getch())
			{
			case 32:
				button = 1;
				break;
			
			case 27:
				printf("Thanks for playing");
				exit(1);
				break;
			}

		}
		
		jump_handler(dino.clear(), button); button = 0;

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
	{
	Sprite(0,0,fileToArray("res/endscreen.bmp"), background).print();
	Screen::display();
	if (_getch() == 27) { printf("Thanks for playing"); return 0; }
	}
	// Restart
	goto restart;
	return 0;
}