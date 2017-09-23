/*ppmtopng uses lodepng by Lode Vandevenne
The program assumes data-only ppm files with a P3 header, i.e. no comments, invalid files or empty lines
Example:
P3
1 3
255
0 0 0 
255 255 255
0 0 0

The above produces a column of black, white, black. 

*/





#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

using namespace std;
using namespace lodepng;

void encodeTwoSteps(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(png, image, width, height);
	if(!error) 
		lodepng::save_file(png, filename);
	if(error) 
		std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

struct RGB {
	int r;
	int g;
	int b;
};

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Invalid args\nUsage: argv[0] infile.ppm outfile.png\n");
		exit(0);
	}


	FILE* ppmfp = fopen(argv[1], "r");
	FILE* pngfp = fopen(argv[2], "w");
	if (!ppmfp) {
		fprintf(stderr, "Invalid filename: %s\n", argv[1]);
		exit(0);
	}
	if (!pngfp) {
		fprintf(stderr, "Invalid filename: %s\n", argv[2]);
		exit(0);
	}
	printf("Reading file %s...\n", argv[1]);
	int width = 0, height = 0, maxcol = 0;
	fscanf(ppmfp, "P3 %d %d %d", &width, &height, &maxcol);
	std::vector<unsigned char> image;
	image.resize(width * height * 4);
	printf("width: %d, height: %d, maxcol: %d\n", width, height, maxcol);
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int r = 0, g = 0, b = 0;
			
			fscanf(ppmfp, "%d %d %d", &r, &g, &b);
			
			image[4 * width * y + 4 * x + 0] = r;//(int) (255.0 * ((float)r / (float)maxcol));
			image[4 * width * y + 4 * x + 1] = g;//(int) (255.0 * ((float)g / (float)maxcol));
			image[4 * width * y + 4 * x + 2] = b;//(int) (255.0 * ((float)b / (float)maxcol));
			image[4 * width * y + 4 * x + 3] = 255;
		}
	}
	fclose(ppmfp);
	printf("done reading\nwriting file %s...\n", argv[2]);
	
	encodeTwoSteps(argv[2], image, width, height);
	printf("done writing\n");
	return 0;
}