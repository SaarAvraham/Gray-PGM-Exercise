#include "q4header.h"





void findRowsAndCols(imgPosList *segments, unsigned int size, unsigned short *rows, unsigned short *cols)
{
	*rows = 0, *cols = 0;//this is the result.
	unsigned int i;
	imgPosCell *pNode;

	for (i = 0; i < size; i++)
	{
		pNode = segments[i].head;
		while (pNode != NULL)
		{
			if (pNode->position[0] > *rows)
				*rows = pNode->position[0];
			if (pNode->position[1] > *cols)
				*cols = pNode->position[1];
			pNode = pNode->next;
		}
	}
	(*rows)++;
	(*cols)++;
}

grayImage *colorSegments(imgPosList *segments, unsigned int size)
{
	grayImage* img;
	unsigned int i;
	short int row, col;
	int currentGreyLevel;
	imgPosCell *pNode;

	img = (grayImage*)(malloc(sizeof(grayImage)));//we allocate a new grayImages.
	if (img == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}

	findRowsAndCols(segments, size, &img->rows, &img->cols);//we find out the max row and col in the segments.


	img->pixels = (unsigned char**)(malloc(img->rows*sizeof(unsigned char*)));
	if (img->pixels == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}

	for (i = 0; i < img->rows; i++)
	{
		img->pixels[i] = (unsigned char*)(malloc(img->cols *sizeof(unsigned char)));//we allocate each row. for example (row: #1)*(8), when cols = 8.
		if (img->pixels == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
	}

	for (i = 0; i < size; i++)
	{

		pNode = segments[i].head;
		if (size == 1)
		{
			currentGreyLevel = 0;
		}
		else
			currentGreyLevel = (int)(i*((double)Max_Value_White / (size - 1)));

		while (pNode != NULL)
		{
			row = pNode->position[0];
			col = pNode->position[1];
			img->pixels[row][col] = (int)currentGreyLevel;
			pNode = pNode->next;
		}
	}

	return img;
}

