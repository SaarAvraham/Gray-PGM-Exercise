

#ifndef header
#define header

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define LEFT 1
#define UPPER_LEFT 2
#define UP 3
#define UPPER_RIGHT 4
#define RIGHT 5
#define LOWER_RIGHT 6
#define DOWN 7
#define LOWER_LEFT 8
#define SAME_PLACE 0

typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _grayImage {
	unsigned short		rows, cols;
	unsigned char **pixels;
}grayImage;

typedef unsigned short imgPos[2];
typedef struct _treeNode {
	imgPos	position;
	treeNodeListCell *next_possible_positions;
}treeNode;


typedef struct _treeNodeListCell {
	treeNode *node;
	struct _treeNodeListCell *next;
}treeNodeListCell;



typedef struct _segment {
	treeNode *root;
}Segment;

Segment findSingleSegment(grayImage* img, imgPos start, unsigned char thershold);

treeNode *findSingleSegmentRec(grayImage* img, imgPos start, unsigned char thershold, imgPos currentPixel, unsigned char** dupliacteCheck);

treeNode* createNewTreeNode(imgPos location);

bool isGoodNeighbor(grayImage* img, unsigned char thershold, int neighborPlace, imgPos start, imgPos currentPixel);

treeNodeListCell* createNode(treeNodeListCell* next);

void freeDuplicateCheck(unsigned char** matrix, unsigned short rows, unsigned short cols);

void insertNodeToHead(treeNodeListCell* newHead, treeNodeListCell* after);

void updateCurrPos(imgPos currentPixelLocation, int neighborPlace, imgPos *neighborPos);

void freeSingleSegment(Segment seg);

void freeSingleSegmentRec(treeNode *root);

Segment findSingleSegment(grayImage* img, imgPos start, unsigned char thershold);

#define isAllocationOK {if ((type) == NULL) { printf("Memory allocation failed\n"); exit(1); }}

#endif
