#include<cstdio>
#include<iostream>
#include<cmath>
#include<bitset>
#include<string>
using namespace std;

pair<int, int> resolution(string filename) {
    FILE * file = fopen(filename.c_str(), "rb");
    int width, height;
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fclose(file);
    return make_pair(width, height);
}

void fileToArray(string filename, char* array[]) {
    FILE * file = fopen(filename.c_str(), "rb");
    short d;
    fseek(file, 18, SEEK_SET);
    int width, height;
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fseek(file, 28, SEEK_SET);
    fread(&d, 2, 1, file);
    if (d != 1) {
        cout << "\nERROR: wrong color depth in file " << filename;
        exit(1);
    }
    // cout << width << ' ' << height << ' ' << d << '\n';
    char array[height][width];
    fseek(file, 62, SEEK_SET);
    for (int h = height - 1; h >= 0; h--) {
        char byte, bits_left, bytes_to_skip = (4 - ((int)ceil( (double)width / 8.0 ) % 4)) % 4;
        bits_left = width;
        while (bits_left > 0) {
            fread(&byte, 1, 1, file);
            int x = 8 - min(8, (int)bits_left);
            for(int bit_mask = pow(2,7); bit_mask >= pow(2, x); bit_mask /= 2)
                array[h][width - bits_left--] = byte & bit_mask ? ' ' : -37;
        }
        fseek(file, bytes_to_skip, SEEK_CUR);
    }
    fclose(file);
}

int main() {
    // string names[] = {"res/run1.bmp","res/run2.bmp","res/jump.bmp","res/enemy.bmp","res/ground.bmp","res/sky.bmp","res/endscreen.bmp"};
    
    // cout << "bytes to skip " << (int)bytes_to_skip << endl;
    // for (int i = 0; i < 16; i++) cout << i; cout << endl;

    return 0;
}