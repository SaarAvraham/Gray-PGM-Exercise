#ifndef header1
#define header1
#include <math.h>
#include "q2header.h"
void saveCompressed(char *file_name, grayImage *image, unsigned char max_gray_level);

int calculateNumOfBits(int maxGrayLevel);
#endif
