
#include "q2header.h"
#include "q5header.h"
#include "q4header.h"
#include "q3header.h"


typedef unsigned char bType;
typedef unsigned char iType;
typedef bType BOOL;
#define TRUE 1
#define FALSE 0
#define BYTE_SIZE 8
#define BYTE_SIZE 8






void saveCompressed(char *file_name, grayImage *image, unsigned char max_gray_level)
{
	int bitsLeftInByte, i = 0, j = 0, bitsFromLastBYTE = 0, currByteFilled = 0, sizeOfPixel, shift, bitsLeftInPixel;
	int counter = 0;
	unsigned char complement, pNewByte = 0x00, pixel, tempData, mask, nextBYTE, leftSideByte;
	FILE *file;
	bool isByteNotFull = false, stopProg = false;
	//sizeOfPixel =calculateNumOfBits(max_gray_level);
	if (max_gray_level == 0 || max_gray_level == 1 || max_gray_level == 3 || max_gray_level == 7 || max_gray_level == 15 || max_gray_level == 31 || max_gray_level == 63 || max_gray_level == 127)
		sizeOfPixel = (unsigned char)(log(max_gray_level + 1) / log(2)); //to find out the number of compressed bits
	else
		sizeOfPixel = (unsigned char)(log(max_gray_level + 1) / log(2)) + 1;
	bitsLeftInByte = 8;
	file = fopen(file_name, "w");
	if (file == NULL)
	{
		printf("Error trying to open file %s\n", file_name);
		exit(1);
	}
	unsigned short temptodelete;

	fwrite(&(image->rows), sizeof(unsigned short), 1, file);
	fwrite(&(image->cols), sizeof(unsigned short), 1, file);
	fwrite(&(max_gray_level), sizeof(unsigned short), 1, file);

	pixel = (unsigned char)((image->pixels[i][j] * max_gray_level) / 255);
	bitsLeftInPixel = sizeOfPixel;
	while (stopProg == false)
	{

		if (bitsLeftInByte > bitsLeftInPixel) // 1000 1001
		{
			tempData = pixel;
			tempData = tempData <<((bitsLeftInByte - bitsLeftInPixel));
			pNewByte = pNewByte | tempData;
			bitsLeftInByte -= bitsLeftInPixel;
			bitsLeftInPixel = 0;
			bitsLeftInPixel = sizeOfPixel;
			j++;
			if (j == image->cols)
			{
				j = 0;
				i++;
				if (i == image->rows)
					stopProg = true;

				if (stopProg != true)
				{
					pixel = (unsigned char)((int)(image->pixels[i][j] * max_gray_level) / 255);
				}
			}
			else
				pixel = (unsigned char)((int)(image->pixels[i][j] * max_gray_level) / 255);

		}
			else
			{
				leftSideByte = pixel >> (bitsLeftInPixel - bitsLeftInByte);
				pNewByte = pNewByte | leftSideByte;
				bitsLeftInPixel -= bitsLeftInByte;
				tempData = pixel;
				tempData = tempData >> bitsLeftInByte;
				nextBYTE = nextBYTE | tempData;
				bitsLeftInByte = 0;
				fwrite(&pNewByte, sizeof(unsigned char), 1, file);
				bitsLeftInByte = 8;

			//	print_binary(pNewByte);
				pNewByte = 0x00;
			}
	}

	if (fclose(file) != 0)
	{
		printf("Error trying to close file\n");
	}

}







