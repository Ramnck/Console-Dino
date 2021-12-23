#include<cstdio>
#include<iostream>
#include<cmath>
#include<bitset>
using namespace std;

int main() {
    FILE * file = fopen("res/bmp.bmp", "rb");
    int w, h;
    short d;
    fseek(file, 18, SEEK_SET);
    fread(&w, 4, 1, file);
    fread(&h, 4, 1, file);
    fseek(file, 28, SEEK_SET);
    fread(&d, 2, 1, file);
    cout << w << ' ' << h << ' ' << d << '\n';
    int array[h];
    fseek(file, 62, SEEK_SET);
    fread(array, 4, 6, file);
    for (int i = 0; i < h; i++)
        cout << array[i] << '\n';
    for (int i = 0; i < h; i++) {
        for (int j = pow(2,7); j > pow(2, 7-w); j /= 2)
            putchar( !(array[i] & j) ? -37 : ' ' );
        putchar('\n');
    }
    return 0;
}