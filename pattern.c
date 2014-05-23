/*
 * pattern.c
 *
 *  Created on: Apr 12, 2014
 *      Author: oo
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pattern.h"

void patternAnalysis(int* binaryImage, int row, int col) {

	int i, j, k;
	int count = 0;

	int* label;
	int* area;
	float* perimeter;
	float* rate;

	//count the number of objects and record the label value for each obj.
	label = (int*) malloc(LABELS * sizeof(int));
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (binaryImage[col * i + j] != BG) {
				for (k = 0; k < count; k++) {
					if (binaryImage[col * i + j] == label[k]) {
						break;
					}
				}
				if (k == count) {
					label[count++] = binaryImage[col * i + j];
				}
			}
		}
	}

	/*	printf("after label of pattern analysis, count= %d\n", count);
	 for(k=0;k<count;k++){
	 printf("No.%d label= %d\t",k+1, label[k]);
	 }
	 */
	//count the area for each obj.
	area = (int*) malloc(count * sizeof(int));
	for (k = 0; k < count; k++) {
		area[k] = 0;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (binaryImage[col * i + j] == label[k]) {
					area[k]++;
				}
			}
		}
	}

	/*	printf("\nafter area of pattern analysis, count= %d\n", count);
	 for(k=0;k<count;k++){
	 printf("No.%d area= %d\n",k+1, area[k]);
	 }
	 */
	//count the perimeter for each obj.
	perimeter = (float*) malloc(count * sizeof(float));
	for (k = 0; k < count; k++) {
		perimeter[k] = calcPerimeter(binaryImage, row, col, label[k]);
		//printf("#%d perimeter= %d\n",k+1, perimeter[k]);

	}

	/*    printf("\nafter perimeter of pattern analysis\n");
	 for(k=0;k<count;k++){
	 printf("#%d perimeter= %d\n",k+1, perimeter[k]);
	 }
	 */
	//check the pattern of each obj.
	rate = (float*) malloc(count * sizeof(float));
	printf("---- Analysis Result: %d object(s) detected in this image ---- \n",
			count);
	for (k = 0; k < count; k++) {
		printf("#%d Object: area =%d, perimeter =%f\n", k + 1, area[k],
				perimeter[k]);
		rate[k] = 4 * PAI * area[k] / (perimeter[k] * perimeter[k]);
		printf("rate = %f\n", rate[k]);
		if (fabs(rate[k] - PAI / 4) < 0.001) {
			printf("Conclusion: Object No.%d  is a square\n\n", k + 1);
		} else if (rate[k] < PAI / 4) {
			printf("Conclusion: Object No.%d is a rectangle\n\n", k + 1);
		} else {
			printf("Conclusion: Object No.%d is a circle\n\n", k + 1);
		}
	}

	free(label);
	free(perimeter);
	free(area);
	free(rate);

}

float calcPerimeter(int* binaryImage, int row, int col, int label) {
	int i, count = 0;
	float perimeter = 0;
	int direction = 7, prevDir = 7;
	int index;
	int position[2 * (row + col)];
	int directionArr[2 * (row + col)];
	int curPosition = -1;
	int size = row * col;

	//find the first border pixel
	for (i = 0; i < row * col; i++) {
		if (binaryImage[i] == label) {
			position[count++] = i;
			index = i;
			//printf("\nfirst elements found at pos. =%d\n", index);
			break;
		}
	}

	//trace the border
	while (curPosition != position[0]) {
		if (direction % 2 == 1) {
			direction = (direction + 6) % 8;
		} else {
			direction = (direction + 7) % 8;
		}
		switch (direction) {
		case 1:
			//printf("dir 1\n");
			if (index - col + 1 < size
					&& binaryImage[index - col + 1] == label) {
				index = index - col + 1;
				direction = 1;
				break;
			}
			if (index - col < size && binaryImage[index - col] == label) {
				index = index - col;
				direction = 2;
				break;
			}
			if (index - col - 1 < size
					&& binaryImage[index - col - 1] == label) {
				index = index - col - 1;
				direction = 3;
				break;
			}
			if (index - 1 < size && binaryImage[index - 1] == label) {
				index = index - 1;
				direction = 4;
				break;
			}
			if (index + col - 1 < size
					&& binaryImage[index + col - 1] == label) {
				index = index + col - 1;
				direction = 5;
				break;
			}
			if (index + col < size && binaryImage[index + col] == label) {
				index = index + col;
				direction = 6;
				break;
			}
			if (index + col + 1 < size
					&& binaryImage[index + col + 1] == label) {
				index = index + col + 1;
				direction = 7;
				break;
			}
			if (index + 1 < size && binaryImage[index + 1] == label) {
				index = index + 1;
				direction = 0;
				break;
			}
			break;
		case 3:
			//printf("dir 3\n");
			if (index - col - 1 < size
					&& binaryImage[index - col - 1] == label) {
				index = index - col - 1;
				direction = 3;
				break;
			}
			if (index - 1 < size && binaryImage[index - 1] == label) {
				index = index - 1;
				direction = 4;
				break;
			}
			if (index + col - 1 < size
					&& binaryImage[index + col - 1] == label) {
				index = index + col - 1;
				direction = 5;
				break;
			}
			if (index + col < size && binaryImage[index + col] == label) {
				index = index + col;
				direction = 6;
				break;
			}
			if (index + col + 1 < size
					&& binaryImage[index + col + 1] == label) {
				index = index + col + 1;
				direction = 7;
				break;
			}
			if (index + 1 < size && binaryImage[index + 1] == label) {
				index = index + 1;
				direction = 0;
				break;
			}
			if (index - col + 1 < size
					&& binaryImage[index - col + 1] == label) {
				index = index - col + 1;
				direction = 1;
				break;
			}
			if (index - col < size && binaryImage[index - col] == label) {
				index = index - col;
				direction = 2;
				break;
			}

			break;
		case 5:
			//printf("dir 5\n");
			if (index + col - 1 < size
					&& binaryImage[index + col - 1] == label) {
				index = index + col - 1;
				direction = 5;
				break;
			}
			if (index + col < size && binaryImage[index + col] == label) {
				index = index + col;
				direction = 6;
				break;
			}
			if (index + col + 1 < size
					&& binaryImage[index + col + 1] == label) {
				index = index + col + 1;
				direction = 7;
				break;
			}
			if (index + 1 < size && binaryImage[index + 1] == label) {
				index = index + 1;
				direction = 0;
				break;
			}
			if (index - col + 1 < size
					&& binaryImage[index - col + 1] == label) {
				index = index - col + 1;
				direction = 1;
				break;
			}
			if (index - col < size && binaryImage[index - col] == label) {
				index = index - col;
				direction = 2;
				break;
			}
			if (index - col - 1 < size
					&& binaryImage[index - col - 1] == label) {
				index = index - col - 1;
				direction = 3;
				break;
			}
			if (index - 1 < size && binaryImage[index - 1] == label) {
				index = index - 1;
				direction = 4;
				break;
			}

			break;
		case 7:
			//printf("dir 7\n");
			if (index + col + 1 < size
					&& binaryImage[index + col + 1] == label) {
				index = index + col + 1;
				direction = 7;
				break;
			}
			if (index + 1 < size && binaryImage[index + 1] == label) {
				index = index + 1;
				direction = 0;
				break;
			}
			if (index - col + 1 < size
					&& binaryImage[index - col + 1] == label) {
				index = index - col + 1;
				direction = 1;
				break;
			}
			if (index - col < size && binaryImage[index - col] == label) {
				index = index - col;
				direction = 2;
				break;
			}
			if (index - col - 1 < size
					&& binaryImage[index - col - 1] == label) {
				index = index - col - 1;
				direction = 3;
				break;
			}
			if (index - 1 < size && binaryImage[index - 1] == label) {
				index = index - 1;
				direction = 4;
				break;
			}
			if (index + col - 1 < size
					&& binaryImage[index + col - 1] == label) {
				index = index + col - 1;
				direction = 5;
				break;
			}
			if (index + col < size && binaryImage[index + col] == label) {
				index = index + col;
				direction = 6;
				break;
			}

			break;
		}

		//increase the perimeter by 1 for regular
		perimeter++;
		//special case
		if (direction % 2 == 1) {
			perimeter = perimeter + 0.41f;
		} else if (direction != prevDir && prevDir % 2 == 0
				&& direction % 2 == 0) {
			perimeter = perimeter + 1;
		}
		/*else if(index == position[0] + col ){
		 //printf("1st point is a corner");
		 perimeter = perimeter +1;
		 }*/

		/*if(direction == directionArr[count-1] && direction%2==1){
		 //printf("contingours 2 bi-direction\n");
		 perimeter = perimeter - 1;
		 }*/

		curPosition = index;
		position[count] = index;
		directionArr[count++] = direction;
		prevDir = direction;
	}
	//increase the perimeter by 1 for the rolling-back to start-point
	perimeter = perimeter + 1;
	return perimeter;
}

int* connectAnalysis(int* binaryImage, int row, int col) {
	int i, j;
	int* connectImage = (int*) malloc(row * col * sizeof(int));

	int west, north, northwest, northeast, current;
	int numObjects = 0;
	int newLabel = 1;

	//the array to resolve labels' equivalence
	int maxNumOfLabels =  row * col * 1/4;
	int* label = (int*) malloc(maxNumOfLabels * sizeof(int));
	for (i = 0; i < row; i++)
		label[i] = i;

	//1st scan to seperate labels
	//1st scan: 1)handle 1st row
	if (binaryImage[0] != BG) {
		connectImage[0] = newLabel++;
		numObjects++;
	} else {
		connectImage[0] = binaryImage[0];
	}
	for (j = 1; j < col; j++) {
		if (binaryImage[j] == BG) {
			connectImage[j] = binaryImage[j];
		} else {
			west = connectImage[j - 1];
			if (west != BG) {
				current = west;
			} else {
				current = newLabel++;
				numObjects++;
			}
			connectImage[j] = current;
		}
	}

	//1st scan: 2)handle the body
	for (i = 1; i < row; i++)
		for (j = 1; j < col - 1; j++) {
			if (binaryImage[i * col + j] == BG) {
				connectImage[i * col + j] = binaryImage[i * col + j];
			} else {
				north = connectImage[(i - 1) * col + j];
				west = connectImage[i * col + j - 1];
				northwest = connectImage[(i - 1) * col + j - 1];
				northeast = connectImage[(i - 1) * col + j + 1];

				if (northwest != BG) {
					if (north == BG && northeast != BG) {
						current = northwest;
						if (label[northwest] != label[northeast]) {
							newPair((int*) label, northeast, northwest,
									newLabel);
							numObjects--;
						}
					} else {
						current = northwest;
					}
				} else if (north != BG) {
					current = north;
				} else if (northeast != BG) {
					if (west != BG && label[west] != label[northeast]) {
						newPair((int*) label, west, northeast, newLabel);
						numObjects--;
					}
					current = northeast;
				} else if (west != BG) {
					current = west;
				} else {
					current = newLabel++;
					numObjects++;
				}

				connectImage[i * col + j] = current;
			}
		}

	//1st scan: 3)handle the 1st column & last column
	for (i = 1; i < row; i++) {
		if (binaryImage[i * col] == BG) {
			connectImage[i * col] = binaryImage[i * col];
		} else {
			north = connectImage[(i - 1) * col];
			northeast = connectImage[(i - 1) * col + 1];
			if (north != BG) {
				current = north;
			} else if (northeast != BG) {
				current = northeast;
			} else {
				current = newLabel++;
				numObjects++;
			}
			connectImage[i * col] = current;
		}

		if (binaryImage[(i + 1) * col - 1] == BG) {
			connectImage[(i + 1) * col - 1] = binaryImage[(i + 1) * col - 1];
		} else {
			north = connectImage[i * col - 1];
			northwest = connectImage[i * col - 2];
			if (northwest != BG) {
				current = northwest;
			} else if (north != BG) {
				current = north;
			} else {
				current = newLabel++;
				numObjects++;
			}
			connectImage[(i + 1) * col - 1] = current;
		}
	}

	//2nd scan to merge labels
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (connectImage[i * row + j] != BG)
				connectImage[i * row + j] = label[connectImage[i * row + j]];
		}
	}

	//printf("Step4::After 2nd Scan:num of Obj found = %d\n", numObjects);
	free(label);
	return connectImage;
}

void newPair(int* label, int label1, int label2, int size) {
	int k;
	for (k = 1; k <= size; k++) {
		if (label[k] == label[label1])
			label[k] = label[label2];
	}
}

int* convertToBinary(int* image, int size, int threshold) {
	int i;
	int* binaryImage = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		if (image[i] <= threshold)
			binaryImage[i] = 0;
		else
			binaryImage[i] = 1;
	}

	return binaryImage;

}

int otsuThreshold(int* histoAry, int size) {
	int threshold;
	double sumColors = 0, sumPixels = 0;
	double sumLowColors = 0, sumLowPixels = 0, avgColors;
	double percentLow, avgColorLow;
	double diff, maxDiff = 0;
	int i, j;

	//calculate the avg grey-level
	for (i = 0; i < size; i++) {
		sumColors += i * histoAry[i];
		sumPixels += histoAry[i];
	}
	avgColors = sumColors / sumPixels;

	for (i = 0; i < size; i++) {
		if (histoAry[i] == 0)
			continue;

		//reset the sum for low colors
		sumLowColors = 0;
		sumLowPixels = 0;

		for (j = 0; j <= i; j++) {
			sumLowColors += j * histoAry[j];
			sumLowPixels += histoAry[j];
		}
		percentLow = sumLowPixels / sumPixels;
		avgColorLow = sumLowColors / sumLowPixels;

		diff = percentLow * (avgColorLow - avgColors)
				* (avgColorLow - avgColors) / (1 - percentLow);

		//calculate the maxDiff for each grey-level
		if (maxDiff < diff) {
			maxDiff = diff;
			threshold = i;
		}
	}
	return threshold;
}

int* getHistoGram(int* ary, int size) {
	int i;
	int* histo = (int*) calloc(COLORS, sizeof(int));
	for (i = 0; i < size; i++) {
		histo[ary[i]]++;
	}
	return histo;
}

