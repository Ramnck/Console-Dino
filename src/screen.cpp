#include<2d/screen.hpp>
#include<2d/sprite.hpp>

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
	system("mode con cols=129 lines=65");
	system("cls");
}

void Screen::pixel(int col, int row, char colour) {
	buffer[row][col] = colour;
}

void Screen::display() {
	for(int i = 0; i < Screen::height; i++) puts(buffer[i]);
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
    // cout << width << ' ' << height << ' ' << d << '\n';
    // char array[height][width];

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

	image* output = new image; output->second = new std::pair<int,int>;
	output->first = array; output->second->first = width; output->second->second = height;

    return output;
}