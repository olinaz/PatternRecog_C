/*
 * P1_PatternRecog_Test.c
 *
 *  Created on: Apr 12, 2014
 *      Author: oo
 */

#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, const char * argv[])
{
	int threshold;
	int row,col,maxcolor;
	char* pgmFile="/Users/oo/Desktop/Eclipse_Projects/CS464_P1_PatternRecog/TestImages/square_and_circle_1024_1024.pgm";
	int* image;

	//read image data into one array from pgm file
	image = getImage(pgmFile, &row, &col, &maxcolor);

    //Step 1: calculate and print the histoGram data
    int* histo = getHistoGram((int*)image, row*col);

    //Step 2: calculate the threshold value via Ostu algo.
	threshold = otsuThreshold(histo,maxcolor);

    //Step 3: convert the grey image into binary image
    int* binaryImage = convertToBinary((int*)image, row*col, threshold);

    //Step 4: connectivity analysis
    int* connectImage = connectAnalysis(binaryImage, row,col);

    //Step5: pattern analysis, can differentiate circle and square only
    patternAnalysis(connectImage, row, col);

    //release the dynamic memory allocated
    free(histo);
    free(binaryImage);
    free(connectImage);
    free(image);
    return 0;
}

