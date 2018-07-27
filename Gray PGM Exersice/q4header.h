
#ifndef header4
#define header4

#include "q1header.h"
#include "q2header.h"
#include "q3header.h"

#define Max_Value_White 255

//Function gets an array of segments (nodes list) and update the rows and columns numbers.
void findRowsAndCols(imgPosList *segments, unsigned int size, unsigned short *rows, unsigned short *cols);

//Function gets an array of segments (nodes list) and return a pointer to a new grayImage that is created from it.
grayImage *colorSegments(imgPosList *segments, unsigned int size);




#endif
