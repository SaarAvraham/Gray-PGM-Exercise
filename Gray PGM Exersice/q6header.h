#ifndef header6
#define header6


#define _CRT_SECURE_NO_WARNINGS
#define GLOBAL_MAX_GRAY_LEVEL 255

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Function gets binary file with compressed image and creates a new PGM file.
void convertCompressedImageToPGM(char* compressed_file_name, char* pgm_file_name);
unsigned char extractBits(unsigned char CurrentByte, int r, int l);

#endif
