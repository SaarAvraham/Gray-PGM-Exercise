#include "q2header.h"
#include "q3header.h"
#include "q1header.h"
#include "q4header.h"
#include "q5header.h"
#include "q6header.h"
#define MaxFileName 261

void main()

{
	int arr[7] = {0};
	grayImage *img = NULL, *colorSegmentsImg = NULL;
	imgPosList **segListArr = NULL;
	int numOfSegments, threshold, maxGrayLevelInput;
	unsigned char maxGrayLevel, choice;
	char fileName[MaxFileName], PGMFileName[MaxFileName];
	bool choiceOn = true, getInput = true;



	while (choiceOn == true)
	{
		if (getInput)
		{
			printf("Please choose an option 1-6:\n");
			printf("1. Read an image file in PGM format\n");
			printf("2. Find all segments\n");
			printf("3. Color the segments\n");
			printf("4. Save the colored image in a compressed format\n");
			printf("5. Compress and save the original image in a compressed format\n");
			printf("6. Convert a compressed image to PGM format\n");
			printf("To exit, enter 7\n");
			scanf("%c", &choice);
			getchar();
		}
		getInput = true;
		switch (choice)
		{
		case '1':
		{
			if (arr[2] == 1)
				freeImage(img);
			arr[2] = 1; //Memory control img
			printf("Please enter the image filename\n");
			scanf("%s", fileName);
			getchar();
			img = readPGM(fileName);
			break;
		}
		case '2':
		{



			if (img == NULL)
			{
				printf("You have to use option 1 before option 2. You will be redirected to option 1 now.\n");
				getInput = false;
				choice = '1';
			}
			else
			{
				if (arr[0] == 1)
				{
					freeSegmentsList(segListArr, numOfSegments);
					free(segListArr);
				}
				segListArr = (imgPosList **)malloc(sizeof(imgPosList *));
				if (segListArr == NULL)
				{
					printf("Memory allocation failed\n");
					exit(1);
				}
				arr[0] = 1; //Memory control segListArr
				printf("Please enter a threshold\n");
				scanf("%d", &threshold);
				getchar();
				numOfSegments = findAllSegments(img, threshold, segListArr);
			}
			break;

		}
		case '3':
		{
			if (segListArr == NULL)
			{
				printf("You have to use option 2 before option 3. You will be redirected to option 2 now.\n");
				getInput = false;
				choice = '2';
			}
			else
			{
				if (arr[1] == 1)
					freeImage(colorSegmentsImg);
				colorSegmentsImg = colorSegments(*segListArr, numOfSegments);
				arr[1] = 1; //colorSegmentsImg
				
			}


			break;
		}
		case '4':
		{
			if (colorSegmentsImg == NULL)
			{
				printf("You have to use option 3 before option 4. You will be redirected to option 3 now.\n");
				getInput = false;
				choice = '3';
			}
			else
			{
				printf("Please enter a file name (the compressed colored image will be written there)\n");
				scanf("%s", fileName);
				getchar();
				printf("Please enter a max gray level (integer lower than 128)\n");
				scanf("%d", &maxGrayLevelInput);
				getchar();
				if (maxGrayLevelInput >= 0 && maxGrayLevelInput <= 127)
				{
				//maxGrayLevel = (unsigned char)maxGrayLevelInput;
				saveCompressed(fileName, colorSegmentsImg, maxGrayLevelInput);
				}

			}


			break;
		}
		case '5':
		{
			if (img == NULL)
			{
				printf("You have to use option 1 before option 5. You will be redirected to option 1 now.\n");
				getInput = false;
				choice = '1';
			}
			else
			{
				printf("Please enter a file name (the compressed image will be written there)\n");
				scanf("%s", fileName);
				getchar();
				printf("Please enter a max gray level (integer lower than 128)\n");
				scanf("%d", &maxGrayLevelInput);
				getchar();
				if (maxGrayLevelInput >= 0 && maxGrayLevelInput <= 127)
				{
					maxGrayLevel = (unsigned char)maxGrayLevelInput;
					saveCompressed(fileName, img, maxGrayLevel);
				}
				else
					printf("Error- The entered number wasn't between 0 and 255. Function will not start.\n You will be redirected to the menu now.\n ");
			}
			break;
		}
		case '6':
		{
			printf("Please enter the compressed image file name\n");
			scanf("%s", fileName);
			getchar();
			printf("Please enter the new file name (the PGM image will be saved there)\n");
			scanf("%s", PGMFileName);
			getchar();
			convertCompressedImageToPGM(fileName, PGMFileName);
			break;
		}
		case '7':
		{
			if (arr[0] == 1)
			{
				freeSegmentsList(segListArr, numOfSegments);
				free(segListArr);
			}
			if (arr[1] == 1)
				freeImage(colorSegmentsImg);
			if( arr[2] == 1)
				freeImage(img);
			
			choiceOn = false;
			printf("Goodbye\n");

			break;
		}
		default:
		{
			printf("Error- entered wrong number, please try again\n");
			break;
		}
		}

	}

}
		
	
	
