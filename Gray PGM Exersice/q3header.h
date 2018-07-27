#ifndef q3header
#define q3header

#include "q2header.h"

typedef struct _imgPosCell
{
	imgPos position;
	struct _imgPosCell *next, *prev;
}imgPosCell;

typedef struct _imgPosList {
	imgPosCell *head, *tail;
}imgPosList;


int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments);
void freePixelsArr(char **arr, int rows, int cols);
void freeSegment(Segment seg);
void freeSegmentRec(treeNode *root);
char ** updatePixelsArr(char **arr, imgPosList *segment);
void copySegmentPositionsToLinkedList(imgPosList *segments, Segment seg, char **pixelsArr);
void copySegmentPositionsToLinkedListRec(imgPosList *segments, treeNode *root, imgPosCell *prev, char **pixelsArr);
void insertNodeToTail(imgPosList **segments, imgPosCell *node, imgPosCell *prev);
bool isEmptyList(imgPosList lst);
imgPosCell * createNewListNode(imgPosList *segments, imgPos position);
char ** createPixelsArr(grayImage *img);
void freeSegmentsList(imgPosList **list, int size);


#endif
