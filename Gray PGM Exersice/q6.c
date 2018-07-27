#define BYTE_SIZE 8
#include "q6header.h"  
#include "q5header.h"

void convertCompressedImageToPGM(char* compressed_file_name, char* pgm_file_name)
{

	FILE* pCompressed, *pRes;
	unsigned short rows, cols;
	int i, j;
	unsigned char maxGrayLevel;
	unsigned char bitRightSide,currPixel, currByte;
	int numOfBitsReadFromCurr = 0, numOfRightRemainedBits, numOfLeftRemainedBits;

	pRes = fopen(pgm_file_name, "w");

	if (pRes == NULL)
	{
		printf("Error trying to open file for writing\n");
		exit(1);
	}

	pCompressed = fopen(compressed_file_name, "rb");
	if (pCompressed == NULL)
	{
		printf("Error trying to open file for reading\n");
		exit(1);
	}
	int numOfBitsInPixel;

	fprintf(pRes, "P2\n");

	fread(&rows, sizeof(unsigned short), 1, pCompressed);
	fread(&cols, sizeof(unsigned short), 1, pCompressed);



	fprintf(pRes, "%hu %hu\n", cols, rows);

	fread(&maxGrayLevel, sizeof(unsigned char), 1, pCompressed);
	fprintf(pRes, "%hu\n", GLOBAL_MAX_GRAY_LEVEL);

	if (maxGrayLevel == 0 || maxGrayLevel == 1 || maxGrayLevel == 3 || maxGrayLevel == 7 || maxGrayLevel == 15 || maxGrayLevel == 31 || maxGrayLevel == 63 || maxGrayLevel == 127)
		numOfBitsInPixel = (unsigned char)(log(maxGrayLevel + 1) / log(2)); //to find out the number of compressed bits
	else
		numOfBitsInPixel = (unsigned char)(log(maxGrayLevel + 1) / log(2)) + 1;


	fread(&currByte, sizeof(unsigned char), 1, pCompressed);
	fread(&currByte, sizeof(unsigned char), 1, pCompressed);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{

			if (numOfBitsReadFromCurr + numOfBitsInPixel > BYTE_SIZE)
			{

				if (numOfBitsReadFromCurr + numOfBitsInPixel - BYTE_SIZE >= 0)
					numOfRightRemainedBits = numOfBitsReadFromCurr + numOfBitsInPixel - BYTE_SIZE;
				else
					numOfRightRemainedBits = (numOfBitsReadFromCurr + numOfBitsInPixel - BYTE_SIZE) * -1;
				numOfLeftRemainedBits = numOfBitsInPixel - numOfRightRemainedBits;
				currPixel = extractBits(currByte, BYTE_SIZE, numOfBitsReadFromCurr + 1);
				currPixel = currPixel << numOfRightRemainedBits;
				fread(&currByte, sizeof(unsigned char), 1, pCompressed);
				bitRightSide = extractBits(currByte, numOfRightRemainedBits, 1);
				numOfBitsReadFromCurr = numOfRightRemainedBits;
				currPixel = currPixel | bitRightSide;
				currPixel =(unsigned char) (currPixel *(GLOBAL_MAX_GRAY_LEVEL /maxGrayLevel));
				fprintf(pRes, "%d ", currPixel);

			}
			else
			{

				currPixel = extractBits(currByte, numOfBitsReadFromCurr + numOfBitsInPixel, numOfBitsReadFromCurr + 1);
				currPixel = (unsigned char)(currPixel *(GLOBAL_MAX_GRAY_LEVEL / maxGrayLevel));
				fprintf(pRes, "%d ", currPixel);
				currPixel = 0;
				numOfBitsReadFromCurr = (numOfBitsReadFromCurr + numOfBitsInPixel) % BYTE_SIZE;
				if (numOfBitsReadFromCurr == 0)
					fread(&currByte, sizeof(unsigned char), 1, pCompressed);
			}
		}
		fprintf(pRes, "\n");
	}
	if (fclose(pCompressed) != 0)
		printf("Error trying to close file \n");
	if (fclose(pRes) != 0)
		printf("Error trying to close file\n");
}





unsigned char extractBits(unsigned char CurrentByte, int r, int l)
{
	unsigned char res, mask;
	int firstShift, secondShift;
	firstShift = l - 1;
	secondShift = BYTE_SIZE - r;

	mask = 0xFF; //1111 1111
	mask = (mask << firstShift) >> firstShift;
	mask = (mask >> secondShift) << secondShift;

	mask = mask & CurrentByte;
	res = mask >> secondShift;

	return res;
}



