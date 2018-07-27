#ifndef q1header
#define q1header

#include "q2header.h"

//Function gets string of file name and read the image into a new grayImage array and return a pointer to it.
grayImage *readPGM(char *fname);

//This function free the grayImage array.
void freeImage(grayImage *img);

#endif
