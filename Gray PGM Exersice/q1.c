
#include "q1header.h"
#include "q2header.h"


grayImage *readPGM(char *fname)
{
	grayImage *img;
	FILE* pTextFile;
	int i, row, col;
	int dummy, maxGrayLevel, pixelValue;
	char ch;
	pTextFile = fopen(fname, "r");
	if (pTextFile == NULL)
	{
		printf("open failed!\n");
		exit(1);
	}
	else
	{

		img = (grayImage*)(malloc(sizeof(grayImage)));//we allocate a new grayImage array.
		if (img == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}

		fscanf(pTextFile, "%c", &ch);//we gets the name - P2.
		fscanf(pTextFile, "%c", &ch);//we gets the name - P2.


		fscanf(pTextFile, "%hu", &img->cols);//we read rows
		fscanf(pTextFile, "%hu", &img->rows);//we read cols
		fscanf(pTextFile, "%d", &maxGrayLevel);//we catch maximum gray level


		img->pixels = (unsigned char**)(malloc(img->rows * sizeof(unsigned char*)));
		if (img->pixels == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}

		for (i = 0; i < img->rows; i++)
		{
			img->pixels[i] = (unsigned char*)(malloc(img->cols * sizeof(unsigned char)));//we allocate each row. 
			if (img->pixels == NULL)
			{
				printf("Memory allocation failed\n");
				exit(1);
			}
		}
		for (row = 0; row < img->rows; row++)//we read the actual pixels.
		{
			for (col = 0; col < img->cols; col++)
			{
				fscanf(pTextFile, "%d", &pixelValue);
				pixelValue =(int) pixelValue*((double)255 / maxGrayLevel);//we convert the pixelValue into the range 0-255.
				img->pixels[row][col] = (unsigned char)pixelValue;
			}
		}
		fclose(pTextFile);
		return img;
	}
}

void freeImage(grayImage *img)
{
	int i;
	for (i = 0; i < (img)->rows; i++)
	{
		free(img->pixels[i]);
	}
	free(img->pixels);
	free(img);
}
