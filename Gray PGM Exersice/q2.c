
#include <stdlib.h>  


#include "q2header.h"
#include "q3header.h"
#include "q4header.h"
#include "q5header.h"

 




//Function frees segment
void freeSingleSegment(Segment seg)
{
	freeSingleSegmentRec(seg.root);
}

void freeSingleSegmentRec(treeNode *root)
{
	treeNodeListCell *p, *tmp;
	if (root == NULL)
		return;
	if (root->next_possible_positions == NULL)
	{
		free(root);
		return;
	}
	else
	{
		p = root->next_possible_positions;
		while (p != NULL)
		{
			tmp = p;
			freeSingleSegmentRec(p->node);
			p = p->next;
			free(tmp);
		}
		free(root);
	}
}


Segment findSingleSegment(grayImage* img, imgPos start, unsigned char thershold)
{
	Segment res;
	int i, j;
	imgPos currPos;

	currPos[0] = start[0];
	currPos[1] = start[1];

	unsigned char** duplicateCheck;
	duplicateCheck = (unsigned char**)malloc(sizeof(unsigned char*)*img->rows);
	if (duplicateCheck == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}

	for (i = 0; i < img->rows; i++)//We create duplicateCheck
	{
		duplicateCheck[i] = (unsigned char*)(malloc(sizeof(unsigned char)*img->cols));
		if (duplicateCheck[i] == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
	}


	for (i = 0; i < img->rows; i++)
	{
		for (j = 0; j < img->cols; j++)
		{
			duplicateCheck[i][j] = '0';
		}
	}
	res.root = findSingleSegmentRec(img, start, thershold, currPos, duplicateCheck);
	freeDuplicateCheck(duplicateCheck, img->rows, img->cols);
	return res;
}

treeNode *findSingleSegmentRec(grayImage* img, imgPos start, unsigned char thershold, imgPos currentPixel, unsigned char** dupliacteCheck)
{
	bool foundFirstNeighbor = false;
	bool isolated = true;
	treeNodeListCell *newNode = NULL;
	treeNode* trNode = NULL;
	int row, col;
	treeNodeListCell* neighbor;
	int neighborsArr[9] = { 0 }, neighborSelect;
	imgPos neighborPos;
	row = currentPixel[0];
	col = currentPixel[1];


	if (img->pixels == NULL)
	{
		return NULL;
	}

	else if (currentPixel[0] >= img->rows || currentPixel[0] < 0 || currentPixel[1] >= img->cols || currentPixel[1] < 0)
		return NULL;

	else
	{
		dupliacteCheck[currentPixel[0]][currentPixel[1]] = '1';

		if (img->rows == 1 && img->cols == 1)
		{
			trNode = createNewTreeNode(currentPixel);
				//return trNode;
		}//check if the "neighboor" is inside the image.
		if (currentPixel[0] < img->rows && currentPixel[0] >= 0 && currentPixel[1] - 1 <= img->cols && currentPixel[1] - 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0]][currentPixel[1] - 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, LEFT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;

					isolated = false;
					neighborsArr[1] = 1;
					dupliacteCheck[currentPixel[0]][currentPixel[1] - 1] = '1';
				}
			}
		}
		if (currentPixel[0] - 1 < img->rows && currentPixel[0] - 1 >= 0 && currentPixel[1] - 1 <= img->cols && currentPixel[1] - 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0] - 1][currentPixel[1] - 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, UPPER_LEFT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[2] = 1;

					dupliacteCheck[currentPixel[0] - 1][currentPixel[1] - 1] = '1';
				}
			}
		}
		if (currentPixel[0] - 1 < img->rows && currentPixel[0] - 1 >= 0 && currentPixel[1] <= img->cols && currentPixel[1] >= 0)
		{
			if (dupliacteCheck[currentPixel[0] - 1][currentPixel[1]] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, UP, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[3] = 1;

					dupliacteCheck[currentPixel[0] - 1][currentPixel[1]] = '1';
				}
			}
		}
		if (currentPixel[0] - 1 < img->rows && currentPixel[0] - 1 >= 0 && currentPixel[1] + 1 <= img->cols && currentPixel[1] + 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0] - 1][currentPixel[1] + 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, UPPER_RIGHT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[4] = 1;

					dupliacteCheck[currentPixel[0] - 1][currentPixel[1] + 1] = '1';
				}
			}
		}
		if (currentPixel[0] < img->rows && currentPixel[0] >= 0 && currentPixel[1] + 1 <= img->cols && currentPixel[1] + 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0]][currentPixel[1] + 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, RIGHT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[5] = 1;
					dupliacteCheck[currentPixel[0]][currentPixel[1] + 1] = '1';
				}
			}
		}
		if (currentPixel[0] + 1 < img->rows && currentPixel[0] + 1 >= 0 && currentPixel[1] + 1 <= img->cols && currentPixel[1] + 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0] + 1][currentPixel[1] + 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, LOWER_RIGHT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[6] = 1;

					dupliacteCheck[currentPixel[0] + 1][currentPixel[1] + 1] = '1';
				}
			}
		}
		if (currentPixel[0] + 1 < img->rows && currentPixel[0] + 1 >= 0 && currentPixel[1] <= img->cols && currentPixel[1] >= 0)
		{
			if (dupliacteCheck[currentPixel[0] + 1][currentPixel[1]] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, DOWN, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;

					isolated = false;
					neighborsArr[7] = 1;

					dupliacteCheck[currentPixel[0] + 1][currentPixel[1]] = '1';
				}
			}
		}
		if (currentPixel[0] + 1 < img->rows && currentPixel[0] + 1 >= 0 && currentPixel[1] - 1 <= img->cols && currentPixel[1] - 1 >= 0)
		{
			if (dupliacteCheck[currentPixel[0] + 1][currentPixel[1] - 1] == '0')//we check duplicates matrix
			{
				if (isGoodNeighbor(img, thershold, LOWER_LEFT, start, currentPixel))
				{
					if (!foundFirstNeighbor)
					{
						trNode = createNewTreeNode(currentPixel);
						foundFirstNeighbor = true;
					}
					newNode = createNode(NULL);
					insertNodeToHead(newNode, trNode->next_possible_positions);
					trNode->next_possible_positions = newNode;
					isolated = false;
					neighborsArr[8] = 1;

					dupliacteCheck[currentPixel[0] + 1][currentPixel[1] - 1] = '1';
				}
			}
		}
		if (isolated)//currentPixel doens't have neighbors.
		{
			if (!foundFirstNeighbor)
			{
				trNode = createNewTreeNode(currentPixel);
				foundFirstNeighbor = true;
			}
			
			//newNode = createNode(NULL); //LEAK!
			//		insertNodeToHead(newNode, trNode->next_possible_positions);
			//	trNode->next_possible_positions = newNode;

			//			trNode->next_possible_positions->node = NULL;
			isolated = false;
			//return trNode;
		}

		neighbor = trNode->next_possible_positions;
		neighborSelect = 1;
		while (neighbor != NULL)
		{
			//	while (neighborsArr[neighborSelect] == 0)
			//		neighborSelect++;
			if (neighborsArr[neighborSelect] == 1)
			{
				updateCurrPos(currentPixel, neighborSelect, &neighborPos);
				neighbor->node = findSingleSegmentRec(img, start, thershold, neighborPos, dupliacteCheck);
				neighbor = neighbor->next;
				neighborSelect++;
			}
			else
				neighborSelect++;

		}
		return trNode;
	}
	/*
	else
	{
	return NULL;
	}
	*/
}

//This function updates a pixel according to neighbor select (see defines)
void updateCurrPos(imgPos currentPixelLocation, int neighborPlace, imgPos *neighborPos)
{
	imgPos res;

	res[0] = currentPixelLocation[0];
	res[1] = currentPixelLocation[1];


	if (res == NULL)
		exit(1);

	switch (neighborPlace)
	{
	case LEFT:
	{
		res[1] = currentPixelLocation[1] - 1;//we go to neighbor's location
		break;
	}
	case UPPER_LEFT:
	{
		res[1] = currentPixelLocation[1] - 1;//we go to neighbor's location
		res[0] = currentPixelLocation[0] - 1;//we go to neighbor's location
		break;
	}
	case UP:
	{
		res[0] = currentPixelLocation[0] - 1;//we go to neighbor's location
		res[1] = currentPixelLocation[1];//we go to neighbor's location
		break;
	}
	case UPPER_RIGHT:
	{
		res[1] = currentPixelLocation[1] + 1;//we go to neighbor's location
		res[0] = currentPixelLocation[0] - 1;//we go to neighbor's location
		break;
	}
	case RIGHT:
	{
		res[0] = currentPixelLocation[0];//we go to neighbor's location
		res[1] = currentPixelLocation[1] + 1;//we go to neighbor's location
		break;
	}
	case LOWER_RIGHT:
	{
		res[1] = currentPixelLocation[1] + 1;//we go to neighbor's location
		res[0] = currentPixelLocation[0] + 1;//we go to neighbor's location
		break;
	}
	case DOWN:
	{
		res[0] = currentPixelLocation[0] + 1;//we go to neighbor's location
		res[1] = currentPixelLocation[1];//we go to neighbor's location
		break;
	}
	case LOWER_LEFT:
	{
		res[1] = currentPixelLocation[1] - 1;//we go to neighbor's location
		res[0] = currentPixelLocation[0] + 1;//we go to neighbor's location
		break;

	}

	}
	(*neighborPos)[0] = res[0];
	(*neighborPos)[1] = res[1];
}

treeNodeListCell* createNode(treeNodeListCell* next)
{
	treeNodeListCell *res;

	res = (treeNodeListCell *)malloc(sizeof(treeNodeListCell));
	if (res == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}

	res->next = next;

	return res;
}

treeNode* createNewTreeNode(imgPos location)
{
	treeNode* trNode;
	trNode = (treeNode*)malloc(sizeof(treeNode));
	if (trNode == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	trNode->position[0] = location[0];
	trNode->position[1] = location[1];

	trNode->next_possible_positions = NULL;

	return trNode;
}

bool isGoodNeighbor(grayImage* img, unsigned char thershold, int neighborPlace, imgPos start, imgPos currentPixel)
{
	unsigned char neighborPixelGrayLevel, startGrayLevel;
	imgPos neighborPixelLocation;

	startGrayLevel = img->pixels[start[0]][start[1]];

	switch (neighborPlace)
	{
	case SAME_PLACE:
	{
		if (startGrayLevel <= thershold)
			return true;
		else return false;
		break;
	}
	case LEFT:
	{
		neighborPixelLocation[1] = currentPixel[1] - 1;//we go to neighbor's location
		neighborPixelLocation[0] = currentPixel[0];//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case UPPER_LEFT:
	{
		neighborPixelLocation[1] = currentPixel[1] - 1;//we go to neighbor's location
		neighborPixelLocation[0] = currentPixel[0] - 1;//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case UP:
	{
		neighborPixelLocation[0] = currentPixel[0] - 1;//we go to neighbor's location
		neighborPixelLocation[1] = currentPixel[1];//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case UPPER_RIGHT:
	{
		neighborPixelLocation[1] = currentPixel[1] + 1;//we go to neighbor's location
		neighborPixelLocation[0] = currentPixel[0] - 1;//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case RIGHT:
	{
		neighborPixelLocation[0] = currentPixel[0];//we go to neighbor's location
		neighborPixelLocation[1] = currentPixel[1] + 1;//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case LOWER_RIGHT:
	{
		neighborPixelLocation[1] = currentPixel[1] + 1;//we go to neighbor's location
		neighborPixelLocation[0] = currentPixel[0] + 1;//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case DOWN:
	{
		neighborPixelLocation[0] = currentPixel[0] + 1;//we go to neighbor's location
		neighborPixelLocation[1] = currentPixel[1];//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	}
	case LOWER_LEFT:
	{
		neighborPixelLocation[1] = currentPixel[1] - 1;//we go to neighbor's location
		neighborPixelLocation[0] = currentPixel[0] + 1;//we go to neighbor's location
		if (neighborPixelLocation[0] >= img->rows || neighborPixelLocation[0] < 0 || neighborPixelLocation[1] >= img->cols || neighborPixelLocation[1] < 0)
			return false;
		else
		{
			neighborPixelGrayLevel = img->pixels[neighborPixelLocation[0]][neighborPixelLocation[1]];
			if (abs(startGrayLevel - neighborPixelGrayLevel) <= thershold)
				return true;
			else return false;
		}
		break;
	default: return false;
	}

	}
}


void insertNodeToHead(treeNodeListCell* newHead, treeNodeListCell* after)
{
	newHead->next = after;
}

void freeDuplicateCheck(unsigned char** matrix, unsigned short rows, unsigned short cols)
{
	int i;
	for (i = 0; i < rows; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}
