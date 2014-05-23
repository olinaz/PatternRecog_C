/*
 * pattern.h
 *
 *  Created on: Apr 12, 2014
 *      Author: oo
 */

#ifndef PATTERN_H_
#define PATTERN_H_

#define COLORS 256
#define FG 1
#define BG 0
#define LABELS 200
#define PAI 3.14

int*  getImage(char * szFileName, int *row,int *col ,int * maxcolor);

void patternAnalysis(int* binaryImage, int row, int col);

float calcPerimeter(int* binaryImage, int row, int col, int label);

int* connectAnalysis(int* binaryImage, int row, int col);

void newPair(int* label, int label1, int label2, int size);

int* convertToBinary(int* image, int size, int threshold);

int otsuThreshold(int* histoAry,int size);

int* getHistoGram(int* ary, int size);


#endif /* PATTERN_H_ */
