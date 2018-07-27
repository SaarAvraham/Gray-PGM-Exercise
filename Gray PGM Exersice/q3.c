

#include "q3header.h"


//This function gets a grayImage, a threshold, and an imgPosList
//The function finds all segments in a given image. 
//The function returns how many segments are there, and updates imgPosList to contain all segments.
//---NOTE: After using this function, when segments are no longer needed, use "freeSegmentsList" function to free allocated memory---
int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments)
{
	Segment temp;
	int segmentsSize = 0, i, j, segmentsIndex = 0, phSize = 1, logSize = 1;
	char **isPartOfSegment; //this arr is used to check if a given pixel is already a part of a segment (1 = part of segment, 0 = not yet part of segment)
	imgPos currPos;
	isPartOfSegment = createPixelsArr(img); //create the pixels arr
	imgPosList *tmp = *segments;
	*segments = (imgPosList *)malloc(sizeof(imgPosList));
	if (*segments == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}

	for (i = 0; i < img->rows; i++)
	{
		for (j = 0; j < img->cols; j++)
		{
			currPos[0] = i;
			currPos[1] = j;

			if (isPartOfSegment[i][j] == 0)
			{
				temp = findSingleSegment(img, currPos, threshold);
				if (logSize > phSize)
				{
					phSize *= 2;
					*segments = (imgPosList *)realloc(*segments, phSize * sizeof(imgPosList));
					if (*segments == NULL)
					{
						printf("Memory allocation failed\n");
						exit(1);
					}
				}
				//segments[segmentsIndex] = (imgPosList *)malloc(sizeof(imgPosList));
				//if (segments[segmentsIndex] == NULL)
				//{
				//	printf("Memory allocation failed\n");
				//	exit(1);
				//}
				((*segments)[segmentsIndex]).head = ((*segments)[segmentsIndex]).tail = NULL;
				copySegmentPositionsToLinkedList(&((*segments)[segmentsIndex]), temp, isPartOfSegment);
				isPartOfSegment = updatePixelsArr(isPartOfSegment, &((*segments)[segmentsIndex]));
				segmentsIndex++;
				logSize++;
				freeSingleSegment(temp); //to free allocated memory by "findSingleSegment" function
			}
		}
	}
	freePixelsArr(isPartOfSegment, img->rows, img->cols);

	return segmentsIndex;

}

//This function frees memory allocated by "findAllSegments" function
void freeSegmentsList(imgPosList **list, int size)
{
	imgPosCell *p, *tmp;
	int i;
	for (i = 0; i < size; i++)
	{
		p = (*list)[i].head;
		while (p != NULL)
		{
			tmp = p;
			p = p->next;
			free(tmp);
		}
	}
	free(*list);
}

//This function frees all memory that was allocated to the pixels arr
void freePixelsArr(char **arr, int rows, int cols)
{
	int i;
	for (i = 0; i < rows; i++)
		free(arr[i]);
	free(arr);
}

//This function gets a segment, and frees all memory that was previously allocated to it
void freeSegment(Segment seg)
{
	freeSegmentRec(seg.root);
}

void freeSegmentRec(treeNode *root)
{
	treeNodeListCell *p, *tmp;
	if (root == NULL)
		return;
	else if (root->next_possible_positions == NULL)
		free(root);
	else
	{
		p = root->next_possible_positions;
		while (p != NULL)
		{
			freeSegmentRec(p->node);
			p = p->next;
		}
		p = root->next_possible_positions;
		while (p != NULL)
		{
			tmp = p;
			p = p->next;
			free(tmp);
		}
	}
}

//This function gets a single segment, and updates the pixel arr at the matching positions to '1'.
char ** updatePixelsArr(char **arr, imgPosList *segment)
{
	imgPosCell *p = segment->head;

	while (p != NULL)
	{
		arr[p->position[0]][p->position[1]] = '1';
		p = p->next;
	}
	return arr;
}

//This function copies a segment nodes into imgPosList
void copySegmentPositionsToLinkedList(imgPosList *segments, Segment seg, char **pixelsArr)
{
	copySegmentPositionsToLinkedListRec(segments, seg.root, NULL, pixelsArr);
}

void copySegmentPositionsToLinkedListRec(imgPosList *segments, treeNode *root, imgPosCell *prev, char **pixelsArr)
{
	imgPosCell *node;
	treeNodeListCell *p;
	if (root == NULL)
		return;
	else if (root->next_possible_positions == NULL && pixelsArr[root->position[0]][root->position[1]] == 0)
	{

		node = createNewListNode(segments, root->position);
		insertNodeToTail(&segments, node, segments->tail);
	}
	else
	{
		p = root->next_possible_positions;
		//while (p != NULL)
		//{
		//	node = createNewListNode(segments, root->position);
		//	insertNodeToTail(&segments, node, prev);
		//	copySegmentPositionsToLinkedListRec(segments, p->node, node);
		//	p = p->next;
		//}
		node = createNewListNode(segments, root->position);
		if (pixelsArr[root->position[0]][root->position[1]] == 0)
			insertNodeToTail(&segments, node, prev);
		else
			free(node);
		while (p != NULL)
		{
			copySegmentPositionsToLinkedListRec(segments, p->node, node, pixelsArr);
			p = p->next;
		}


	}
}

//This function inserts a new node to the head of a linked list
void insertNodeToHead2(imgPosList **segments, imgPosCell *node, imgPosCell *prev)
{
	if (isEmptyList(**segments))
		(*segments)->head = (*segments)->tail = node;
	else
	{
		node->next = (*segments)->head;
		node->prev = NULL;
		(*segments)->head = node;
	}
}

//This function inserts a node to the tail
void insertNodeToTail(imgPosList **segments, imgPosCell *node, imgPosCell *prev)
{
	if (isEmptyList(**segments))
		(*segments)->head = (*segments)->tail = node;
	else
	{
		node->prev = prev;
		(*segments)->tail->next = node;
		(*segments)->tail = node;
	}
}


bool isEmptyList(imgPosList lst)
{
	return (lst.head == NULL && lst.tail == NULL);
}

//This function creates a new list node
imgPosCell * createNewListNode(imgPosList *segments, imgPos position)
{
	imgPosCell *node = (imgPosCell *)malloc(sizeof(imgPosCell));
	if (node == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	node->next = node->prev = NULL;
	node->position[0] = position[0];
	node->position[1] = position[1];
	return node;
}

//This function gets a pointer to grayImage
//The fucntion creates and returns a 2d array of chars (cells set to 0), with the same dimensions as the grayImage (rows * cols)
char ** createPixelsArr(grayImage *img)
{
	char **res;
	int i;
	//--------------Allocating memory to isPartOfSegment (setting cells to 0)-------------------//
	res = (char **)calloc(img->cols, sizeof(char *));
	if (res == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	for (i = 0; i < img->rows; i++)
	{
		res[i] = (char *)calloc(img->cols, sizeof(char));
		if (res[i] == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
	}
	return res;
}
