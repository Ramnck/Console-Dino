#include<2d/screen.hpp>
#include<2d/sprite.hpp>

void setConsole(int width, int height) {
    std::string text = "mode con cols=";
    text += std::to_string(width);
    text += " lines=";
    text += std::to_string(height);
    system(text.c_str());
}

void Screen::init(int width, int height) {
    Screen::width = width;
    Screen::height = height;
    _COORD coord = {height, width};
    _SMALL_RECT Rect = {0,0,coord.X - 1, coord.Y - 1};
	
    setConsole(width, height);

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Screen::buffer = new char[height*width];
    Screen::console_handler = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); 

	SetConsoleActiveScreenBuffer(Screen::console_handler);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
    SetConsoleScreenBufferSize(Handle, coord);
    Screen::clear();
}

void Screen::pixel(int col, int row, char colour) {
	buffer[(row * width) + col] = colour;
}

void Screen::clear() { memset(Screen::buffer, ' ', Screen::height * Screen::width); }

void Screen::display() {
    Screen::buffer[Screen::width * Screen::height - 1] = '\0';
    WriteConsoleOutputCharacter(Screen::console_handler, (LPCSTR) Screen::buffer, Screen::width * Screen::height + 1, { 0, 0 }, &Screen::bytes_written);
}

void Screen::fill() {
    memset(Screen::buffer, -37, Screen::width * Screen::height);
    for(int i = 0; i < Screen::width; i++)
        Screen::buffer[i] = (i%16) < 10 ? '0' + (i%16) : 'A' + (i%16) - 10;
    Screen::display();
}

image* fileToArray(std::string filename) {
    FILE * file = fopen(filename.c_str(), "rb");
	if (!file) { printf("%s does not exist", filename.c_str()); exit(1);}
    short d;
    fseek(file, 18, SEEK_SET);
    int width, height;
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fseek(file, 28, SEEK_SET);
    fread(&d, 2, 1, file);
    if (d != 1) { printf("\nERROR: wrong color depth in file %s\n",filename); exit(1); }

    // if (width != 128 && width != 16 || height != 16 && height != 64) {printf("ERROR: wrong resolution in file %s", filename.c_str()); exit(1);}

    char** array = new char*[height]; for(int i = 0; i < height; i++) array[i] = new char[width];

    fseek(file, 62, SEEK_SET);
    for (int h = height - 1; h >= 0; h--) {
        char byte, bytes_to_skip = (4 - ((int)std::ceil( (double)width / 8.0 ) % 4)) % 4;
        int bits_left;
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

	image* output = new image;
	output->bmp = array; output->w = width; output->h = height;

    return crop(output);
}