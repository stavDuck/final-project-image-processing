#include "FinalProject_316464775_208522649.h"

const int k2Mask[2][2] = { {0,2},{3,1} };
const int k3Mask[3][3] = { {2,6,4},{5,0,1},{8,3,7} };
const int k4Mask[4][4] = { {0,8,2,10},{12,4,14,6},{3,11,1,9},{15,7,13,5} };

// *********************
//* question 1 */
// *********************

//This function gets a PPM file with Magic Number P3.
//It gets the data from the file and creates a new color image and returns it.
COLOR_IMAGE* readPPM(char* fname)
{
	COLOR_IMAGE* image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));
	FILE* fp;

	//open text file for reading
	fp = fopen(fname, "r");
	checkFileOpening(fp);
	checkAllocation(image);

	getHeaderPPMData(fp, image);
	getBodyPPMData(fp, image);

	fclose(fp);
	return image;
}

//This function gets an image file and an image. It sets the image struct according to the file.
void getBodyPPMData(FILE* fp, COLOR_IMAGE* image)
{
	int i, j;
	short int num;

	image->pixels = (RGB**)malloc((image->rows) * sizeof(RGB*));
	checkAllocation(image->pixels);

	for (i = 0; i < image->rows; i++)
	{
		image->pixels[i] = (RGB*)malloc((image->cols) * sizeof(RGB));
		checkAllocation(image->pixels[i]);

		if (fgetc(fp) == '\n');

		for (j = 0; j < image->cols; j++)
		{
			fscanf(fp, "%hd", &num);
			image->pixels[i][j].r = (unsigned char)num;

			fscanf(fp, "%hd", &num);
			image->pixels[i][j].g = (unsigned char)num;

			fscanf(fp, "%hd", &num);
			image->pixels[i][j].b = (unsigned char)num;
		}
	}
}

//This function gets a pointer to a file and a pointer to an image. 
//It gets the header data from the image file and puts it in the image struct.
//This function is suitable for ALL kinds of files.
void getHeaderPPMData(FILE* fp, COLOR_IMAGE* image)
{
	// counts how many values are saved
	int saveDataInd = MAGIC_NUMBER;
	char c;

	while (saveDataInd <= 4)
	{
		fscanf(fp, " %c", &c);
		//check if comment
		if (c == '#')
			skipComment(fp);
		//if c is a white space - skip it
		else if (c == '\n');

		else
		{
			//move the indicator back
			fseek(fp, -1, SEEK_CUR);
			setHeaderPPMValuesToImage(fp, image, saveDataInd);
			saveDataInd++;
		}
	}
}

//This function gets a pointer to a file, a pointer to an image and an indicator
//to which data already entered to image struct.
//The function enters the data to the struct.
void setHeaderPPMValuesToImage(FILE* fp, COLOR_IMAGE* image, int saveDataInd)
{
	int depth, num;

	switch (saveDataInd)
	{
	case MAGIC_NUMBER:
		// skip the image format
		fseek(fp, 2, SEEK_CUR);
		break;

	case COLS:
	{
		fscanf(fp, "%d", &num);
		image->cols = (unsigned short int)num;
	}
	break;

	case ROWS:
	{
		fscanf(fp, "%d", &num);
		image->rows = (unsigned short int)num;
	}
	break;

	case DEPTH:
		fscanf(fp, "%d", &depth);
		break;
	}
}

//This function gets a pointer to a file and skips the comment, until new line
void skipComment(FILE* fp)
{
	while ((fgetc(fp)) != '\n');
}

// This function checks if the file has opened. If not - exits with code 1.
void checkFileOpening(FILE* fp)
{
	if (fp == NULL)
	{
		printf("File did not open!\n");
		exit(1);
	}
}

// *********************
//* question 2 */
// *********************

//This function gets a PGM file with Magic Number P2.
//It gets the data from the file and creates a new gray image and returns it.
GRAY_IMAGE* readPGM(char* fname)
{
	GRAY_IMAGE* image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));
	FILE* fp;

	//open text file for reading
	fp = fopen(fname, "r");
	checkFileOpening(fp);
	checkAllocation(image);

	getHeaderPGMData(fp, image);
	getBodyPGMData(fp, image);

	fclose(fp);
	return image;
}

//This function gets a pointer to a file and a pointer to a gray image. 
//It gets the header data from the image file and puts it in the image struct.
void getHeaderPGMData(FILE* fp, GRAY_IMAGE* image)
{
	// counts how many values are saved
	int saveDataInd = MAGIC_NUMBER;
	char c;

	while (saveDataInd <= 4)
	{
		fscanf(fp, " %c", &c);
		//check if comment
		if (c == '#')
			skipComment(fp);
		else if (c == '\n'); //////////////////attentionnnnnnnnnnnnnnnnn || c == '\r'

		else
		{
			//move the indicator back
			fseek(fp, -1, SEEK_CUR);
			setHeaderPGMValuesToImage(fp, image, saveDataInd);
			saveDataInd++;
		}
	}
}

//This function gets an image file and an image. It sets the image struct according to the file.
void getBodyPGMData(FILE* fp, GRAY_IMAGE* image)
{
	int i, j, num;

	image->pixels = (unsigned char**)malloc(image->rows * sizeof(unsigned char*));
	checkAllocation(image->pixels);

	for (i = 0; i < image->rows; i++)
	{
		image->pixels[i] = (unsigned char*)malloc((image->cols) * sizeof(unsigned char));
		checkAllocation(image->pixels[i]);

		for (j = 0; j < image->cols; j++)
		{
			fscanf(fp, "%d", &num);
			image->pixels[i][j] = (unsigned char)num;
		}

		if (fgetc(fp) == '\n');
	}
}

//This function gets a pointer to a file, a pointer to a gray image and an indicator
//to which data already entered to image struct.
//The function enters the data to the struct.
void setHeaderPGMValuesToImage(FILE* fp, GRAY_IMAGE* image, int saveDataInd)
{
	int depth, num;

	switch (saveDataInd)
	{
	case MAGIC_NUMBER:
		// skip the image format
		fseek(fp, 2, SEEK_CUR);
		break;

	case COLS:
	{
		fscanf(fp, "%d", &num);
		image->cols = (unsigned short int)num;
	}
	break;

	case ROWS:
	{
		fscanf(fp, "%d", &num);
		image->rows = (unsigned short int)num;
	}
	break;

	case DEPTH:
		fscanf(fp, "%d", &depth);
		break;
	}
}

// *********************
//* questions 3+4 */
// *********************

//This function recieves an image, threshold value and an empty segments array. 
//It finds all segments in image, inserts them as Image Position List array and returns the array size.
int findAllSegments(GRAY_IMAGE* img, unsigned char threshold, IMG_POS_LIST** segments)
{
	IMG_POS_LIST* tempSeg;
	SEGMENT resSeg;
	IMG_POS start;
	int i, j, logSize = 0, physicalSize = 1, rows = img->rows, cols = img->cols;
	// create boolian flag array
	bool** flagArray = boolianHelperArray(rows, cols);
	// allocate array of pointers to IMG POS lists
	tempSeg = (IMG_POS_LIST*)malloc(physicalSize * sizeof(IMG_POS_LIST));
	checkAllocation(tempSeg);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			// if flag arr pos == false
			if (flagArray[i][j] == false)
			{
				// get single segment
				start[0] = i;
				start[1] = j;
				resSeg = findSingleSegment(img, start, threshold);

				// check size of temp seg and allocate if needed
				if (logSize == physicalSize)
				{
					physicalSize *= 2;
					tempSeg = (IMG_POS_LIST*)realloc(tempSeg, physicalSize * sizeof(IMG_POS_LIST));
					checkAllocation(tempSeg);
				}

				tempSeg[logSize] = createImagePositionListFromSingleSegment(&resSeg, flagArray);
				logSize++;
			}

		}
	}

	freeBoolArray(flagArray, rows);
	tempSeg = (IMG_POS_LIST*)realloc(tempSeg, logSize * sizeof(IMG_POS_LIST));
	*segments = tempSeg;
	return logSize;
}

//This function calls createImagePositionListFromSingleSegmentHelper function and returns a pointer to Image Position list
//which contains all positions of one segment.
IMG_POS_LIST createImagePositionListFromSingleSegment(SEGMENT* segment, bool** flagArray)
{
	IMG_POS_LIST newList;
	makeEmptyPositionList(&newList);
	createImagePositionListFromSingleSegmentHelper(segment->root, flagArray, &newList);
	return newList;
}

//This is a recursive function. It returns an Image Position list
//which contains all positions of one segment.
void createImagePositionListFromSingleSegmentHelper(TNODE* root, bool** flagArray, IMG_POS_LIST* newList)
{
	TNODE_LNODE* curr = root->nextPossiblePositions.head;

	// flag the root 
	flagArray[root->position[0]][root->position[1]] = true;
	insertDataToEndPositionList(newList, root->position);

	if (curr == NULL) // no neighbors
		return;

	else // there are neighbors
	{
		while (curr != NULL)
		{
			createImagePositionListFromSingleSegmentHelper(curr->node, flagArray, newList);
			curr = curr->next;
		}
	}
}

// Function input: get pointer from any type
// Function check if memory allocated succesfuly, if not exist the program
void checkAllocation(void* lst)
{
	if (lst == NULL)
	{
		printf("Allocation failed!!!\n");
		exit(1);
	}
}

//This function uses the findSingleSegmentHelper function. 
//It gets an img array, a start point and a threshold value and returns a segment tree.
SEGMENT findSingleSegment(GRAY_IMAGE* img, IMG_POS start, unsigned char threshold)
{
	SEGMENT res;
	bool** flagArray = boolianHelperArray(img->rows, img->cols);

	res.root = createNewTreeNode(start[0], start[1]);
	res.root->nextPossiblePositions = findSingleSegmentHelper(img, flagArray, start, start, threshold);

	freeBoolArray(flagArray, img->rows);
	return res;
}

//This is a recursive function. 
//This function finds a single segment.
//It returns a list (Tree List) of the start neighbors.
TNODE_LIST findSingleSegmentHelper(GRAY_IMAGE* img, bool** flagArray, IMG_POS originalStart, IMG_POS start, unsigned char threshold)
{
	TNODE_LNODE* curr;
	TNODE_LIST lstTemp;

	lstTemp = listValidPosition(img, flagArray, originalStart, start, threshold);
	curr = lstTemp.head;

	// check smallest input
	if (curr == NULL)
		return;

	else //there is at least one neighbor
	{
		// max 8 times loop for each neighbor
		while (curr != NULL)
		{
			curr->node->nextPossiblePositions = findSingleSegmentHelper(img, flagArray, originalStart, curr->node->position, threshold);
			curr = curr->next;
		}

		return lstTemp;
	}
}

//This function creates an array of boolian values. The function initializes the array to fales values.
bool** boolianHelperArray(int rows, int cols)
{
	bool** res = (bool**)malloc((rows) * sizeof(bool*));
	checkAllocation(res);

	int i, j;
	for (i = 0; i < rows; i++)
	{
		res[i] = (bool*)malloc((cols) * sizeof(bool));
		checkAllocation(res[i]);

		for (j = 0; j < cols; j++)
		{
			res[i][j] = false;
		}
	}
	return res;
}

//Funcion gets an image, a start point, a neighbor expressed in x,y coordinates and a threshold value.
//It checks if the neighbor is valid.
//Valid neighbors are neighbors within the image array + neighbors are in the threshold range.
//Returns true if valid
bool checkNeighborValid(GRAY_IMAGE* img, IMG_POS start, short x, short y, unsigned char threshold)
{
	int cols = img->cols, rows = img->rows;

	//check that neighbor is in the image + threshold
	return ((x < rows&& x >= 0) && (y < cols&& y >= 0) && checkThreshold(img, start, x, y, threshold));
}

//Funcion gets an image and a start point, return a list of the valid neighbors
//valid neighbors are neighbors within the image array + neighbors are in the threshold range
TNODE_LIST listValidPosition(GRAY_IMAGE* img, bool** flagArray, IMG_POS originalStart, IMG_POS start, unsigned char threshold)
{
	TNODE_LIST list;
	TNODE* res;
	int rows = img->rows, cols = img->cols;
	short x, y;
	x = start[0];
	y = start[1];

	// flag the start pixel
	flagArray[x][y] = true;

	makeEmptyList(&list);

//check image boundries + threshold + if not already inserted as a neighbor

	// check upper center
	if ((x - 1 >= 0) && (checkThreshold(img, originalStart, x - 1, y, threshold)) && (flagArray[x - 1][y] == false))
	{
		res = createNewTreeNode(x - 1, y);
		insertDataToEndList(&list, res);
		flagArray[x - 1][y] = true;
	}

	// check upper right
	if ((x - 1 >= 0 && y + 1 < cols) && (checkThreshold(img, originalStart, x - 1, y + 1, threshold)) && (flagArray[x - 1][y + 1] == false))
	{
		res = createNewTreeNode(x - 1, y + 1);
		insertDataToEndList(&list, res);
		flagArray[x - 1][y + 1] = true;
	}

	// check x row right (center is the start)
	if ((y + 1 < cols) && (checkThreshold(img, originalStart, x, y + 1, threshold)) && (flagArray[x][y + 1] == false))
	{
		res = createNewTreeNode(x, y + 1);
		insertDataToEndList(&list, res);
		flagArray[x][y + 1] = true;
	}

	// check down right
	if ((x + 1 < rows && y + 1 < cols) && (checkThreshold(img, originalStart, x + 1, y + 1, threshold)) && (flagArray[x + 1][y + 1] == false))
	{
		res = createNewTreeNode(x + 1, y + 1);
		insertDataToEndList(&list, res);
		flagArray[x + 1][y + 1] = true;
	}

	// check down center
	if ((x + 1 < rows) && (checkThreshold(img, originalStart, x + 1, y, threshold)) && (flagArray[x + 1][y] == false))
	{
		res = createNewTreeNode(x + 1, y);
		insertDataToEndList(&list, res);
		flagArray[x + 1][y] = true;
	}

	// check down left
	if ((x + 1 < rows && y - 1 >= 0) && (checkThreshold(img, originalStart, x + 1, y - 1, threshold)) && (flagArray[x + 1][y - 1] == false))
	{
		res = createNewTreeNode(x + 1, y - 1);
		insertDataToEndList(&list, res);
		flagArray[x + 1][y - 1] = true;
	}

	// check x row left
	if ((y - 1 >= 0) && (checkThreshold(img, originalStart, x, y - 1, threshold)) && (flagArray[x][y - 1] == false))
	{
		res = createNewTreeNode(x, y - 1);
		insertDataToEndList(&list, res);
		flagArray[x][y - 1] = true;
	}

	// check left upper index
	if ((x - 1 >= 0 && y - 1 >= 0) && (checkThreshold(img, originalStart, x - 1, y - 1, threshold)) && (flagArray[x - 1][y - 1] == false))
	{
		res = createNewTreeNode(x - 1, y - 1);
		insertDataToEndList(&list, res);
		flagArray[x - 1][y - 1] = true;
	}

	return list;
}

//This function check if the neighbor of the start is in the threshold range.
//Returns True if in range
bool checkThreshold(GRAY_IMAGE* img, IMG_POS start, short x, short y, unsigned char threshold)
{
	int referenceVal = img->pixels[start[0]][start[1]];
	int currVal = img->pixels[x][y];

	return ((referenceVal - threshold) <= currVal && (referenceVal + threshold) >= currVal);
}

//This function creates an empty list
void makeEmptyList(TNODE_LIST* lst)
{
	lst->head = lst->tail = NULL;
}

//This function creates a new list node
TNODE_LNODE* createNewListNode(TNODE* node, TNODE_LNODE* next)
{
	TNODE_LNODE* res;
	res = (TNODE_LNODE*)malloc(sizeof(TNODE_LNODE));
	checkAllocation(res);

	res->node = node;
	res->next = next;
	return res;
}

//This function inserts data to the end of a list
void insertDataToEndList(TNODE_LIST* lst, TNODE* node)
{
	TNODE_LNODE* newTail;
	newTail = createNewListNode(node, NULL);
	insertNodeToEndList(lst, newTail);
}

//This function inserts a node to the end of a list
void insertNodeToEndList(TNODE_LIST* lst, TNODE_LNODE* tail)
{
	if (lst->head == NULL)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

//This function creates an empty list
void makeEmptyTreeList(TNODE_LIST* lst)
{
	lst->head = lst->tail = NULL;
}

//This function creates a new Tree Node.
TNODE* createNewTreeNode(short x, short y)
{
	TNODE* res = (TNODE*)malloc(sizeof(TNODE));
	checkAllocation(res);

	res->position[0] = x;
	res->position[1] = y;
	makeEmptyTreeList(&res->nextPossiblePositions);

	return res;
}

//This function free a bool pointer array.
void freeBoolArray(bool** arr, int rows)
{
	int i;
	for (i = 0; i < rows; i++)
		free(arr[i]);

	free(arr);
}

//This function creates an empty list
void makeEmptyPositionList(IMG_POS_LIST* lst)
{
	lst->head = lst->tail = NULL;
}

//This function creates a new list node
IMG_POS_NODE* createNewListPositionNode(IMG_POS position, IMG_POS_NODE* next, IMG_POS_NODE* prev)
{
	IMG_POS_NODE* res;
	res = (IMG_POS_NODE*)malloc(sizeof(IMG_POS_NODE));
	checkAllocation(res);

	res->position[0] = position[0];
	res->position[1] = position[1];
	res->next = next;
	res->prev = prev;
	return res;
}

//This function inserts data to the end of a list
void insertDataToEndPositionList(IMG_POS_LIST* lst, IMG_POS position)
{
	IMG_POS_NODE* newTail;
	newTail = createNewListPositionNode(position, NULL, NULL);
	insertNodeToEndPositionList(lst, newTail);
}

//This function inserts a node to the end of a list
void insertNodeToEndPositionList(IMG_POS_LIST* lst, IMG_POS_NODE* tail)
{
	if (lst->head == NULL)
	{
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;
	}
	else
	{
		tail->prev = lst->tail;
		tail->next = NULL;
		lst->tail->next = tail;
		lst->tail = tail;
	}
}

// *********************
//* questin 5 */
// *********************

//This function recieves a list of segments and it's size. 
//The funcion determines the segment's value by it's index in the list;
//The calculation for the value for index i is (i*(255/(size-1)).
//The function return a gray image.
GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments, unsigned int size)
{
	int cols, rows;
	GRAY_IMAGE* grayImage = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));
	checkAllocation(grayImage);

	//get max x y from function
	getMaxFromSegmentList(segments, size, &rows, &cols);
	grayImage->cols = cols + 1;
	grayImage->rows = rows + 1;

	//allocate gray image according to max x y
	allocateGrayImagePixelArr(grayImage);

	//get data from segment and fill the image with segments val
	fillGrayImagePixels(grayImage, segments, size);

	return grayImage;
}

//This function recieves a pointer to a gray image, an array of segments and it's size.
//The function fill the image pixels according to the algorithem.
void fillGrayImagePixels(GRAY_IMAGE* image, IMG_POS_LIST* segments, unsigned int size)
{
	IMG_POS_NODE* curr;
	int i;

	for (i = 0; i < size; i++)
	{
		curr = segments[i].head;
		while (curr != NULL)
		{
			image->pixels[curr->position[0]][curr->position[1]] = i * ((double)MAX_PIXEL_VALUE / (size - 1));
			curr = curr->next;
		}
	}
}

//This function recieves a pointer to a gray image and allocates the pixels array in it.
void allocateGrayImagePixelArr(GRAY_IMAGE* image)
{
	int i;
	image->pixels = (unsigned char**)malloc(image->rows * sizeof(unsigned char*));
	checkAllocation(image->pixels);

	for (i = 0; i < image->rows; i++)
	{
		image->pixels[i] = (unsigned char*)malloc(image->cols * sizeof(char));
		checkAllocation(image->pixels[i]);
	}
}

//This function recieves an array of image position lists and the size of it.
//It returns the max x and y to determine the size of the image.
void getMaxFromSegmentList(IMG_POS_LIST* segment, unsigned int size, int* x, int* y)
{
	int i, maxX, maxY;
	IMG_POS_NODE* curr = segment[0].head;

	maxX = curr->position[0];
	maxY = curr->position[1];

	for (i = 1; i < size; i++)
	{
		curr = segment[i].head;

		while (curr != NULL)
		{
			if (curr->position[0] > maxX)
				maxX = curr->position[0];
			if (curr->position[1] > maxY)
				maxY = curr->position[1];
			curr = curr->next;
		}
	}
	*x = maxX;
	*y = maxY;
}

// *********************
//* question 6 */
// *********************

//This function recieves a file name, a gray image pointer and a gray max level value.
//Function compresses the image data into a binary file.
void saveCompressed(char* fname, GRAY_IMAGE* image, unsigned char maxGrayLevel) 
{
	// calculate new max gray level
	int i, j, resPrevRemind = 0;
	int lengthZipByte = getLengthZipByte(maxGrayLevel);
	bool extraSpaceInPrev = false;
	unsigned char prevCompressPixel, currCompressPixel;

	FILE* compressedGrayFile = fopen(fname, "wb");
	checkAllocation(compressedGrayFile);

	setCompressedHeader(compressedGrayFile, image, maxGrayLevel);

	// set pixel [0,0] in place
	prevCompressPixel = ((image->pixels[0][0] * maxGrayLevel) / MAX_PIXEL_VALUE);
	prevCompressPixel = prevCompressPixel << (BYTE_LENGTH - lengthZipByte); // shift to the left
	resPrevRemind = BYTE_LENGTH - lengthZipByte;

	for (i = 0; i < image->rows; i++)
	{
		for (j = 0; j < image->cols; j++) 
		{
			if (i == 0 && j==0) // 0,0 was calculated
				j++;
			extraSpaceInPrev = false;
			// calculate the zipped pixel
			currCompressPixel = ((image->pixels[i][j] * maxGrayLevel) / MAX_PIXEL_VALUE);
			resPrevRemind = calculatePrevAndCurrBytes(&prevCompressPixel, &currCompressPixel, lengthZipByte, resPrevRemind, &extraSpaceInPrev); 

			// if false - prev pixel is not full yet
			if (extraSpaceInPrev == false)
			{
				// write to file the prev
				fwrite(&prevCompressPixel, sizeof(unsigned char), 1, compressedGrayFile);

				// set prev = curr zipped pixel
				prevCompressPixel = currCompressPixel;
			}
		}
	}
	//enter the last byte - check if there is more space
	//if prev has more space, then curr is irrelevant
	if (extraSpaceInPrev)
		fwrite(&prevCompressPixel, sizeof(unsigned char), 1, compressedGrayFile);

	//if there is more bits to enter to byte - print curr
	else if (resPrevRemind > 0 && extraSpaceInPrev==false)
		fwrite(&currCompressPixel, sizeof(unsigned char), 1, compressedGrayFile);

	fclose(compressedGrayFile);
}

//This function recieves pointers to binary file, a gray image and max gray level
//It writes the cols, rows and gray max level to the file
void setCompressedHeader(FILE* fp, GRAY_IMAGE* grayImage, unsigned char maxGrayLevel)
{
	fwrite(&grayImage->rows, sizeof(unsigned short), 1, fp);
	fwrite(&grayImage->cols, sizeof(unsigned short), 1, fp);
	fwrite(&maxGrayLevel, sizeof(unsigned char), 1, fp);
}

// Function get the new max grey
// calculate and return how many bits for every pixel
int getLengthZipByte(unsigned char newMaxGrey)
{
	int count = 0, saver = newMaxGrey;
	
	while (newMaxGrey > 0) {
		count++;
		newMaxGrey = newMaxGrey / 2;
	}

	if (pow(2, count) < saver)
		count++;

	return count;
}

// Function get prev byte and curr byte with the length of the ziped pixel 
// and the space need to be filled at the prev byte,
// Function updates but prev and curr byte and retun the number of remind bits in the curr after calculation
int calculatePrevAndCurrBytes(unsigned char* prevByte, unsigned char* currByte, int lengthZipByte, int prevRemind, bool *extraSpaceInPrev)
{
	int remindLengthCurr = lengthZipByte - prevRemind; // calculate how much space in curr Byte need to insert
	unsigned char prevTemp = *prevByte;
	unsigned char currTemp = *currByte;
	unsigned char addToPrev;

	if (prevRemind > lengthZipByte) // there is enough space for full pixel in the middle of a byte
	{
		remindLengthCurr *= -1;
		currTemp = currTemp << remindLengthCurr;
		prevTemp += currTemp;
		*extraSpaceInPrev = true;
	}
	else if (prevRemind > 0)  // need to insert some of the curre to the prev space
	{
		// need to add the to prev the remind peice from the curr
		addToPrev = currTemp >> remindLengthCurr; // get only the extra part in curr
		prevTemp += addToPrev; // no prev is full with 8 bits

		// need to shift curr to the left
		currTemp = currTemp << BYTE_LENGTH - remindLengthCurr;
	}
	else { // = 0
		// no need to add to prev - preve byte is full
		// need to shift letft curr according to lengthZipByte
		currTemp = currTemp << (BYTE_LENGTH - lengthZipByte);
	}

	*prevByte = prevTemp; // full BYTE
	*currByte = currTemp; // remind curr shifted to the left size
	
	if (*extraSpaceInPrev)
		return remindLengthCurr;
	else
		return (BYTE_LENGTH - remindLengthCurr); // return how much space left in current byte
}

// *********************
//* question 7 */
// *********************

//This function recieves a gray file name, creates a new gray file in PGM P2 format and 
//writes the converted compressed data into the new file.
void convertCompressedImageToPGM(char* fname)
{
	int i,j, numOfBits, prevLength = 0;
	unsigned short rows, cols;
	unsigned char maxGrayLevel, prevCompressPixel, currCompressPixel, originalVal;
	FILE* newGrayFile, * compressedFile;
	char* newFileName = (char*)malloc((strlen(fname) + 5)); // +".pgm" + '\0'
	checkAllocation(newFileName);

	// open a file for reading
	compressedFile = fopen(fname, "rb");
	checkFileOpening(compressedFile);

	// create a new name for new file, in PGM P2 format
	sprintf(newFileName, "%s%s", fname, ".pgm");
	
	newGrayFile = fopen(newFileName, "w");
	checkFileOpening(newGrayFile);

	getHeaderDataFromCompressedFile(compressedFile, &rows, &cols, &maxGrayLevel);
	
	// write header
	writeImageHeader(newGrayFile, P2_FORMAT, (int)cols, (int)rows, MAX_PIXEL_VALUE);
	
	// get how many bits represent one pixel
	numOfBits = getLengthZipByte(maxGrayLevel);

	//convert and print first byte
	fread(&prevCompressPixel, sizeof(unsigned char), 1, compressedFile); 
	currCompressPixel = prevCompressPixel;
			
	prevLength = BYTE_LENGTH; 

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++) // first was calculated
		//while(j<cols)
		{
			if(prevLength <= numOfBits)
				//get the next one
				fread(&currCompressPixel, sizeof(unsigned char), 1, compressedFile);

			prevLength = calculatePrevAndCurrCompressed(&prevCompressPixel, &currCompressPixel, numOfBits, prevLength);
			//convert to regular pixel
			originalVal = ((prevCompressPixel * MAX_PIXEL_VALUE) / maxGrayLevel);
			//print to file
			fprintf(newGrayFile, "%3d ", originalVal); //print to new file P2 format 	
			//overwrite
			prevCompressPixel = currCompressPixel;
			//j++;
		}
		fprintf(newGrayFile, "\n");
	}

	fclose(compressedFile);
	fclose(newGrayFile);
}

//This function recievs a previous byte, a current one, num of bit per pixel value and the length of the current
//byte. It converts the compressed values to original pixels and returns the length of the next byte.
int calculatePrevAndCurrCompressed(unsigned char* prevByte, unsigned char* currByte, int numOfBits, int lengthPrev)
{
	int newLength=0, prevRemind = numOfBits - lengthPrev; 
	unsigned char prevTemp = *prevByte;
	unsigned char currTemp = *currByte;
	unsigned char addToPrev;

	if (prevRemind > 0) //need to take extra bits from curr byte
	{
		//free space for remind bit
		prevTemp = prevTemp << prevRemind;
		// take the remind bit from curr and shift right to make space to sum prev and curr
		addToPrev = currTemp >> (BYTE_LENGTH - prevRemind);
		//sum prev and curr
		prevTemp += addToPrev;
		//update for next round
		currTemp = currTemp << prevRemind;
		currTemp = currTemp >> prevRemind;
		//update length
		newLength = BYTE_LENGTH - prevRemind;
	}

	else if (prevRemind < 0) //there is a full pixel in the middle of a byte
	{
		//convert to positive
		prevRemind *= -1;
		//save extra data for next round
		currTemp = currTemp << (BYTE_LENGTH - prevRemind);
		currTemp = currTemp >> (BYTE_LENGTH - prevRemind);
		//shift prev to recieve full data
		prevTemp = prevTemp >> prevRemind;
		//update length for next round
		newLength = prevRemind;
	}

	else //prevRemind = 0
		newLength = BYTE_LENGTH;

	*prevByte = prevTemp;
	*currByte = currTemp;

	return newLength; // lengthPrev
}

//This function recieves a poiter to compressed file and gets the data from the compressed file, 
//then returns it in output values.
void getHeaderDataFromCompressedFile(FILE* compressedFile, int* rows, int* cols, unsigned char* maxGrayLevel)
{
	fread(rows, sizeof(unsigned short), 1, compressedFile);
	fread(cols, sizeof(unsigned short), 1, compressedFile);
	fread(maxGrayLevel, sizeof(unsigned char), 1, compressedFile);
}


// *********************
//* question 8 */
// *********************

//This function recives a file name of a color image in PPM P3.
//It converts the color image into a gray image and creates a gray image file.
void convertPPMToPGM(char* fname)
{
	bool isBinaryFile = false;
	FILE* colorFile, * grayFile;
	char* newFileName;
	char* openFuncColorFile, openFuncGrayile;
	COLOR_IMAGE* colorImage;
	int depth;
	newFileName = createNewFileName(fname, PGM_TYPE);

	colorFile = fopen(fname, "r");
	checkFileOpening(colorFile);
	grayFile = fopen(newFileName, "w");
	checkFileOpening(grayFile);

	// get image depth (works for both bin and txt files)
	depth = getImageDepth(colorFile);

	// Create Color Image Object
	colorImage = readPPM(fname);

	// Write to gray file from created colored image
	writePGMFileFromPPMImage(grayFile, colorImage, depth, isBinaryFile);

	// all close and free statments
	fclose(colorFile);
	fclose(grayFile);
	freeColorImage(colorImage);
	free(newFileName);
}

// This function recives pointer to gray file, pointer to color image and depth value
// Function writes to the gray image file
//void writePGMFileFromPPMImage(FILE* grayFile, COLOR_IMAGE* colorImage, int depth)
void writePGMFileFromPPMImage(FILE* grayFile, COLOR_IMAGE* colorImage, int depth, bool isFileBinary)
{
	// if file is binary Greay write body
	if (isFileBinary) {
		writeImageHeader(grayFile, P5_FORMAT, colorImage->cols, colorImage->rows, depth);
		writePGMImageBody_Binary(grayFile, colorImage);
	}
	// else file is txt write body
	else {
		writeImageHeader(grayFile, P2_FORMAT, colorImage->cols, colorImage->rows, depth);
		writePGMImageBody(grayFile, colorImage);
	}
}

//This function recieves an image file (PPM/PGM) and the header parameters
//It writes the header part in the file.
void writeImageHeader(FILE* imageFile, char* imageType, int cols, int rows, int depth)
{
	fprintf(imageFile, "%s\n%d %d\n%d\n", imageType, cols, rows, depth);
}

//This function recieves a pointer to a gray image file and a pointer to a color image.
//It converts the color body image to gray image and writes to a gray image file in P2 format.
void writePGMImageBody(FILE* grayFile, COLOR_IMAGE* colorImage)
{
	int i, j, num;
	for (i = 0; i < colorImage->rows; i++)
	{
		for (j = 0; j < colorImage->cols; j++)
			fprintf(grayFile, "%3d ", convertColorPixelToGrayPixel(colorImage->pixels[i][j]));

		fprintf(grayFile, "\n");
	}
}

//This function recieves color pixel and returns a gray pixel.
int convertColorPixelToGrayPixel(RGB pixel)
{
	return ((int)(pixel.r + pixel.b + pixel.g) / 3);
}

//This function creates a file name for a gray picture file, same as  file + ".XXX" ending
//(XXX represent the ending)
//It returns the file name as a string
char* createNewFileName(char* fname, char* endingStr)
{
	int write, i, length = strlen(fname) + 1;
	char* res = (char*)malloc((length + 1) * sizeof(char));
	checkAllocation(res);

	sprintf(res, "%s", fname);

	write = length - 4; // 4 for ending type (ppm/pgm) index start from 0

	for (i = 0; i < IMAGE_TYPE_SIZE; i++)
	{
		res[write] = endingStr[i];
		write++;
	}

	res[length] = '\0';
	return res;
}

//This function gets a pointer to a file. 
//It gets the header data from the image file and returns the image depth.
int getImageDepth(FILE* fp)
{
	// counts how many values are saved
	int depth = EOF, saveDataInd = MAGIC_NUMBER;
	char c;

	while (saveDataInd <= 4)
	{
		fscanf(fp, " %c", &c);
		//check if comment
		if (c == '#')
			skipComment(fp);
		else if (c == '\n');

		else
		{
			//move the indicator back
			fseek(fp, -1, SEEK_CUR);
			scanHeaderDataToFindDepth(fp, saveDataInd, &depth);
			saveDataInd++;
		}

	}
	return depth;
}

//This function gets a pointer to a file, a pointer to an image and an indicator
//to which data already entered to image struct.
//The function enters the data to the struct.
void scanHeaderDataToFindDepth(FILE* fp, int saveDataInd, int* depth)
{
	int tmpDepth, num;

	switch (saveDataInd)
	{
	case MAGIC_NUMBER:
		// skip the image format
		fseek(fp, 2, SEEK_CUR);
		break;

	case COLS:
	{
		fscanf(fp, "%d", &num);
	}
	break;

	case ROWS:
	{
		fscanf(fp, "%d", &num);
	}
	break;

	case DEPTH:
	{
		fscanf(fp, "%d", &tmpDepth);
		*depth = tmpDepth;
	}
	break;
	}
}

// *********************
//* question 9 */
// *********************

//This function recieves a gray image file name. 
//It creates a gray image and converts it to three PGM P2 format black and white images
//according to a k mask (k=2,k=3,k=4).
void convertPGMToBW(char* fname)
{
	//bool isBinaryFile = false;
	FILE* grayFile, * K2bwImage, * K3bwImage, * K4bwImage;
	char* k2Name, * k3Name, * k4Name;
	char* openFuncGrayFile, openFuncBWFile, imageMagicNum;
	GRAY_IMAGE* grayImage;
	int depth;

	// open gray file
	grayFile = fopen(fname, "r");
	checkFileOpening(grayFile);

	// get depth - func for both bin and txt files
	depth = getImageDepth(grayFile);

	//files creation. NOTE - according to the project instructions,
	//the black and white image depth is always 1 = white
	//Create file names according to mask k index
	k2Name = createBlackWhiteFileName(fname, K2);
	k3Name = createBlackWhiteFileName(fname, K3);
	k4Name = createBlackWhiteFileName(fname, K4);

	// Open new BW files
	K2bwImage = fopen(k2Name, "w");
	checkFileOpening(K2bwImage);
	K3bwImage = fopen(k3Name, "w");
	checkFileOpening(K3bwImage);
	K4bwImage = fopen(k4Name, "w");
	checkFileOpening(K4bwImage);

	grayImage = readPGM(fname);

	// write header works for both func for bin/txt
	writeImageHeader(K2bwImage, P2_FORMAT, grayImage->cols, grayImage->rows, WHITE);
	writeImageHeader(K3bwImage, P2_FORMAT, grayImage->cols, grayImage->rows, WHITE);
	writeImageHeader(K4bwImage, P2_FORMAT, grayImage->cols, grayImage->rows, WHITE);

	writeBlackWhiteBodyFromPGM(K2bwImage, grayImage, K2, depth);
	writeBlackWhiteBodyFromPGM(K3bwImage, grayImage, K3, depth);
	writeBlackWhiteBodyFromPGM(K4bwImage, grayImage, K4, depth);

	// close and free statments
	fclose(K2bwImage);
	fclose(K3bwImage);
	fclose(K4bwImage);
	free(k2Name);
	free(k3Name);
	free(k4Name);
	fclose(grayFile);
	freeGrayImage(grayImage);
}

//This function recieves a pointer to a file to write to, a pointer to a picture
//a k indicator to a relevant mask and the depth of the picture
void writeBlackWhiteBodyFromPGM(FILE* fp, GRAY_IMAGE* grayImage, int k, int depth)
{
	int i, j, indexPixel, res, size = k * k, range = (depth + 1) / size;

	for (i = 0; i < grayImage->rows; i++)
	{
		for (j = 0; j < grayImage->cols; j++)
		{
			//if range=0, all values in matrix will turn to 0
			if (range == 0)
				indexPixel = 0;
			else
				//calculate new pixel according to range table
				indexPixel = ((int)grayImage->pixels[i][j]) / range;
			//calculate black or white index according to k mask
			res = calculateBlackWhiteIndex(k, indexPixel, i % k, j % k);
			//print index to file
			fprintf(fp, "%3d ", res);
		}
		fprintf(fp, "\n");
	}
}

//This function recieves k num, indexPixel, row and col.
//It calculates the black/white value according to the algorithem with a suitable k mask.
//It returns the black/white value.
int calculateBlackWhiteIndex(int k, int indexPixel, int row, int col)
{
	if (k == K2)
	{
		if (k2Mask[row][col] < indexPixel)
			return WHITE;
		else
			return BLACK;
	}

	else if (k == K3)
	{
		if (k3Mask[row][col] < indexPixel)
			return WHITE;
		else
			return BLACK;
	}

	else
	{
		if (k4Mask[row][col] < indexPixel)
			return WHITE;
		else
			return BLACK;
	}
}

//This function creates a name for a black and white image file.
char* createBlackWhiteFileName(char* fname, int k)
{
	bool stop = false;
	int write = 0, i = 0, length = strlen(fname) + 4; // bw+k+\0
	char* endingStr = (char*)malloc(8 * sizeof(char));
	char* res = (char*)malloc(length * sizeof(char));
	checkAllocation(res);
	checkAllocation(endingStr);

	sprintf(endingStr, "%s%d%s%s", "bw", k, ".", PGM_TYPE);

	while (stop == false)
	{
		if (fname[i] != '.')
		{
			res[write] = fname[i];
			i++;
			write++;
		}
		else
			stop = true;
	}
	res[write] = '\0';

	strcat(res, endingStr);

	free(endingStr);
	return res;
}

// *********************
//* question 10 */
// *********************

//This function gets a PPM file with Magic Number P6.
//It gets the data from the file and creates a new color image and returns it.
COLOR_IMAGE* readPPM_Binary(char* fname)
{
	COLOR_IMAGE* image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));
	FILE* fp;

	//open text file for reading
	fp = fopen(fname, "rb");
	checkFileOpening(fp);
	checkAllocation(image);

	getHeaderPPMData(fp, image);
	getBodyPPMData_Binary(fp, image);

	fclose(fp);
	return image;
}

//This function gets an image file and an image. It sets the image struct according to the file.
void getBodyPPMData_Binary(FILE* fp, COLOR_IMAGE* image)
{
	int i, j;
	unsigned char value;

	image->pixels = (RGB**)malloc(image->rows * sizeof(RGB*));
	checkAllocation(image->pixels);

	if (fgetc(fp) == '\n');

	for (i = 0; i < image->rows; i++)
	{
		image->pixels[i] = (RGB*)malloc((image->cols) * sizeof(RGB));
		checkAllocation(image->pixels[i]);

		for (j = 0; j < image->cols; j++)
		{
			fread(&(image->pixels[i][j].r), sizeof(unsigned char), 1, fp);
			fread(&(image->pixels[i][j].g), sizeof(unsigned char), 1, fp);
			fread(&(image->pixels[i][j].b), sizeof(unsigned char), 1, fp);
		}
	}
}

//This function recives a file name of a color image in PPM P6.
//It converts the color image into a gray image and creates a gray image file.
void convertPPMToPGM_Bin(char* fname)
{
	bool isBinaryFile = true;
	FILE* colorFile, * grayFile;
	char* newFileName;
	char* openFuncColorFile, openFuncGrayile;
	COLOR_IMAGE* colorImage;
	int depth;
	newFileName = createNewFileName(fname, PGM_TYPE);

	colorFile = fopen(fname, "rb");
	checkFileOpening(colorFile);
	grayFile = fopen(newFileName, "wb");
	checkFileOpening(grayFile);

	// get image depth (works for both bin and txt files)
	depth = getImageDepth(colorFile);

	// Create Color Image Object
	colorImage = readPPM_Binary(fname);

	// Write to gray file from created colored image
	writePGMFileFromPPMImage(grayFile, colorImage, depth, isBinaryFile);

	// all close and free statments
	fclose(colorFile);
	fclose(grayFile);
	free(newFileName);
	freeColorImage(colorImage);
}

//This function recieves a pointer to a gray image file and a pointer to a color image.
//It converts the color body image to gray image and writes to a gray image file in P2 format.
void writePGMImageBody_Binary(FILE* grayFile, COLOR_IMAGE* colorImage)
{
	int i, j;
	unsigned char grayIndex;
	for (i = 0; i < colorImage->rows; i++)
	{
		for (j = 0; j < colorImage->cols; j++)
		{
			grayIndex = (colorImage->pixels[i][j].r + colorImage->pixels[i][j].g + colorImage->pixels[i][j].b) / 3;
			fwrite(&grayIndex, sizeof(unsigned char), 1, grayFile);
		}
	}
}

// *********************
//* question 11 */
// *********************

//This function recieves a gray image file name with binary format. 
//It creates a gray image and converts it to three PGM P5 format black and white images
//according to a k mask (k=2,k=3,k=4).
void convertPGMToBW_Bin(char* fname) 
{
	FILE* grayFile, * K2bwImage, * K3bwImage, * K4bwImage;
	char* k2Name, * k3Name, * k4Name;
	char* openFuncGrayFile, openFuncBWFile, imageMagicNum;
	GRAY_IMAGE* grayImage;
	int depth;

	// open gray file
	grayFile = fopen(fname, "rb");
	checkFileOpening(grayFile);

	// get depth - func for both bin and txt files
	depth = getImageDepth(grayFile);

	//files creation. NOTE - according to the project instructions,
	//the black and white image depth is always 1 = white
	// Create file names according to mask k index
	k2Name = createBlackWhiteFileName(fname, K2);
	k3Name = createBlackWhiteFileName(fname, K3);
	k4Name = createBlackWhiteFileName(fname, K4);

	// Open new BW files
	K2bwImage = fopen(k2Name, "wb");
	checkFileOpening(K2bwImage);
	K3bwImage = fopen(k3Name, "wb");
	checkFileOpening(K3bwImage);
	K4bwImage = fopen(k4Name, "wb");
	checkFileOpening(K4bwImage);

	// create object of Gray image
	grayImage = readPGM_Binary(fname);

	// write header works for both func for bin/txt
	writeImageHeader(K2bwImage, P5_FORMAT, grayImage->cols, grayImage->rows, WHITE);
	writeImageHeader(K3bwImage, P5_FORMAT, grayImage->cols, grayImage->rows, WHITE);
	writeImageHeader(K4bwImage, P5_FORMAT, grayImage->cols, grayImage->rows, WHITE);

	// write BW file body 
	writeBlackWhiteBodyFromPGM_Binary(K2bwImage, grayImage, K2, depth);
	writeBlackWhiteBodyFromPGM_Binary(K3bwImage, grayImage, K3, depth);
	writeBlackWhiteBodyFromPGM_Binary(K4bwImage, grayImage, K4, depth);

	// close and free statments
	fclose(K2bwImage);
	fclose(K3bwImage);
	fclose(K4bwImage);
	free(k2Name);
	free(k3Name);
	free(k4Name);
	fclose(grayFile);
	freeGrayImage(grayImage);
}

//This function recieves a pointer to a file to write to, a pointer to a picture
//a k indicator to a relevant mask and the depth of the picture
void writeBlackWhiteBodyFromPGM_Binary(FILE* fp, GRAY_IMAGE* grayImage, int k, int depth)
{
	int i, j, indexPixel, res, size = k * k, range = (depth + 1) / size;

	for (i = 0; i < grayImage->rows; i++)
	{
		for (j = 0; j < grayImage->cols; j++)
		{
			//if range=0, all values in matrix will turn to 0
			if (range == 0)
				indexPixel = 0;
			else
			{
				//calculate new pixel according to range table
				indexPixel = ((int)grayImage->pixels[i][j]) / range;
			}

			//calculate black or white index according to k mask
			res = calculateBlackWhiteIndex(k, indexPixel, i % k, j % k);

			//print index to file
			fwrite(&res, sizeof(unsigned char), 1, fp);
		}
	}
}

//This function gets a PGM file with Magic Number P5.
//It gets the data from the file and creates a new gray image and returns it.
GRAY_IMAGE* readPGM_Binary(char* fname)
{
	GRAY_IMAGE* image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));
	FILE* fp;

	//open text file for reading
	fp = fopen(fname, "rb");
	checkFileOpening(fp);
	checkAllocation(image);

	getHeaderPGMData(fp, image);
	getBodyPGMData_Binary(fp, image);

	fclose(fp);
	return image;
}

//This function gets an image file and an image. It sets the image struct according to the file type.
void getBodyPGMData_Binary(FILE* fp, GRAY_IMAGE* image)
{
	int i, j;
	unsigned char value;

	image->pixels = (unsigned char**)malloc(image->rows * sizeof(unsigned char*));
	checkAllocation(image->pixels);

	if (fgetc(fp) == '\n');

	for (i = 0; i < image->rows; i++)
	{
		image->pixels[i] = (unsigned char*)malloc((image->cols) * sizeof(unsigned char));
		checkAllocation(image->pixels[i]);

		for (j = 0; j < image->cols; j++)
		{
			fread(&value, sizeof(unsigned char), 1, fp);
			image->pixels[i][j] = value;
		}	
	}
}


// *********************
//* question 12 */
// *********************

//This function prints the menu and asks the user to choose an option.
//It activates the menu according the the user's input.
void menu()
{
	printf("Hello,\n");
	printMenu();
	activateUsersChoice();
}

//This function checks if the user's input matches the menu options.
//It return true if it does, false if it doesn't.
bool checkValidInput(int num)
{
	return(num > 0 && num < 12);
}

//This function activates the menu. it recieves the user's choice and activates the suitable function.
void activateUsersChoice()
{
	COLOR_IMAGE* colorImage = NULL;
	GRAY_IMAGE* grayImage = NULL;
	IMG_POS_LIST* segmentsList = NULL;
	
	int size, newChoice, tempTreshold, tempMaxGray;
	unsigned char threshold, maxGrayLevel;
	char* fileName;

	scanf("%d", &newChoice);
	while (checkValidInput(newChoice))
	{

		switch (newChoice)
		{
		case 1:
		{
			printf("Please enter a PPM (p3) file name:\n");
			fileName = getFileNameFromUser();
			colorImage = readPPM(fileName);
		}
		break;
		case 2:
		{
			printf("Please enter a PGM (p2) file name:\n");
			fileName = getFileNameFromUser();
			grayImage = readPGM(fileName);
		}
		break;
		case 3:
		{
			if (grayImage == NULL)
				printf("No gray image! Please go back to option 2.\n");
							
			else
			{
				printf("Please enter the desired threshold value:\n");
				scanf("%d", &tempTreshold);
				threshold = tempTreshold + '0';
				size = findAllSegments(grayImage, threshold, &segmentsList);
			}
		}
		break;
		case 4:
		{
			if (segmentsList == NULL)
				printf("No segments list! Please go back to option 3.\n");
	
			else
				grayImage = colorSegments(segmentsList, size);
		}
		break;
		case 5:
		{
			if (grayImage == NULL)
				printf("No gray image! Please go back to option 4.\n");

			else
				createANewPGMFormatP2File(grayImage);
		}
		break;
		case 6:
		{
			if (grayImage == NULL)
				printf("No gray image! Please go back to option 2.\n");
			else
			{
				printf("Please enter a PGM file name and a maximun gray level value:\n");
				fileName = getFileNameFromUser();
				scanf("%d", &tempMaxGray);
				maxGrayLevel = tempMaxGray + '0';
				saveCompressed(fileName, grayImage, maxGrayLevel);
			}
		}
		break;
		case 7:
		{
			printf("Please enter a compressed image file name:\n");
			fileName = getFileNameFromUser();
			if (checkIfFileExists(fileName))
				convertCompressedImageToPGM(fileName);
			else
				printf("Compressed file does not exist!\nPlease go back to option 6.\n");
		}
		break;
		case 8:
		{
			printf("Please enter a PPM (p3) file name:\n");
			fileName = getFileNameFromUser();
			if (checkIfFileExists)
				convertPPMToPGM(fileName);
			else
				printf("File does not exist!\nPlease enter an existing file name!\n");
		}
		break;
		case 9:
		{
			printf("Please enter a PGM (p2) file name:\n");
			fileName = getFileNameFromUser();
			if (checkIfFileExists)
				convertPGMToBW(fileName);
			else
				printf("File does not exist!\nPlease enter an existing file name!\n");
		}
		break;
		case 10:
		{
			printf("Please enter a PPM (p6) file name:\n");
			fileName = getFileNameFromUser();
			if (checkIfFileExists)
				convertPPMToPGM_Bin(fileName);
			else
				printf("File does not exist!\nPlease enter an existing file name!\n");
		}
		break;
		case 11:
		{
			printf("Please enter a PGM (p5) file name:\n");
			fileName = getFileNameFromUser();
			if (checkIfFileExists)
				convertPGMToBW_Bin(fileName);
			else
				printf("File does not exist!\nPlease enter an existing file name!\n");
		}
		break;
		case 12:
			exit(1);
			break;
		}
		printMenu();
		scanf("%d", &newChoice);
	}
	
	if(colorImage != NULL)
		freeColorImage(colorImage);
	if(grayImage != NULL)
		freeGrayImage(grayImage);
}

//This function recieves a pointer to a gray image and frees it.
void freeGrayImage(GRAY_IMAGE* image)
{
	int i, j;
	for (i = 0; i < image->rows; i++)
	{
		free(image->pixels[i]);
	}
	free(image->pixels);
	free(image);
}

//This function recieves a pointer to a color image and frees it.
void freeColorImage(COLOR_IMAGE* image)
{
	int i;
	for (i = 0; i < image->rows; i++)
	{
		free(image->pixels[i]);
	}
	free(image->pixels);
	free(image);
}

//This function checks if the file name exists in memory.
bool checkIfFileExists(char* fname)
{
	FILE* fp;
	fp = fopen(fname, "r");
	if (fp == NULL)
		return false;
	else
		return true;

	fclose(fp);
}

//This function gets input from user and returns a string (a file name).
//If the file name entered is without a pgm ending - the function will add the ending.
char* getFileNameFromUser()
{
	char c, * res;
	int physicalSize = 2, logicalSize = 0, checkEnding;
	res = (char*)malloc(physicalSize * sizeof(char));
	checkAllocation(res);

	scanf("\n%c", &c);
	
	while (c != '\n')
	{
		if (physicalSize == logicalSize + 1)
		{
			physicalSize *= 2;
			res = (char*)realloc(res, physicalSize * sizeof(char));
			checkAllocation(res);
		}
		res[logicalSize] = c;
		logicalSize++;

		scanf("%c", &c);
	}

	res = (char*)realloc(res, (logicalSize + 1) * sizeof(char));
	checkAllocation(res);
	
	res[logicalSize] = '\0';
	//check if user entered file name with ending
	checkEnding = checkIfUserEnteredEndingFile(res);
	if (checkEnding == -1)
	{
		res = (char*)realloc(res, (logicalSize + 5) * sizeof(char));
		checkAllocation(res);
		sprintf(res, "%s%s", res, ".pgm");
	}

	return res;
}

//This file checks if the user entered a file name with or without an ending.
//It recieves the file name and returns the '.' index if there's and ending or -1 if there is no ending.
int checkIfUserEnteredEndingFile(char* name)
{
	int index=0;

	while (name[index] != '.' && name[index] != '\0')
		index++;

	if (name[index] == '.')
		return index;
	else
		return -1;
}

//This file creates a new PGM P2 format file from gray image data.
void createANewPGMFormatP2File(GRAY_IMAGE* image)
{
	int depth;
	FILE* newFile;
	char* newFileName;
	
	printf("Please enter a name for the new file:\n");
	newFileName = getFileNameFromUser();
	
	newFile = fopen(newFileName, "w");
	
	depth = getDepthFromGrayImage(image);
	writeImageHeader(newFile, P2_FORMAT, image->cols, image->rows, depth);
	writePGMFileBodyFromGrayImage(newFile, image);

	fclose(newFile);
}

//This function recieves a gray image and finds it's depth.
//It returns the image depth.
unsigned char getDepthFromGrayImage(GRAY_IMAGE* image)
{
	int i, j;
	unsigned char maxVal=0;
	bool stopIfMax = false;

	for (i = 0; i < image->rows && (stopIfMax == false); i++)
	{
		for (j = 0; j < image->cols && (stopIfMax == false); j++)
		{
			if (maxVal < image->pixels[i][j])
			{
				if (image->pixels[i][j] == MAX_PIXEL_VALUE)
					stopIfMax = true;
				
				maxVal = image->pixels[i][j];
			}
		}
	}

	return maxVal;
}

//This function recieves a pointer to a gray image file and a pointer to a gray image.
//It writes to a gray image file in P2 format.
void writePGMFileBodyFromGrayImage(FILE* grayFile, GRAY_IMAGE* grayImage)
{
	int i, j, num;
	for (i = 0; i < grayImage->rows; i++)
	{
		for (j = 0; j < grayImage->cols; j++)
			fprintf(grayFile, "%d ", grayImage->pixels[i][j]);

		fprintf(grayFile, "\n");
	}
}

//This function prints the menu.
void printMenu()
{
	printf("\033[0;36m");
	printf("**********************\n");
	printf("*        MENU        *\n");
	printf("**********************\n");
	printf("\033[0m");
	printf("Please choose one of the menu options:\n");
	printf("1. Read an image file in PPM (p3) format\n");
	printf("2. Read an image file in PGM(p2) format\n");
	printf("3. Find all segments\n");
	printf("4. Color the segments\n");
	printf("5. Save the colored image to PGM\n");
	printf("6. Compress and save the original image in a compressed format\n");
	printf("7. Convert a compressed image to PGM format\n");
	printf("8. Convert PPM to PGM(p3->p2)\n");
	printf("9. Convert PGM to BW(p2->p2)\n");
	printf("10. Convert PPM to PGM(p6->p5)\n");
	printf("11. Convert PGM to BW(p5->p5)\n");
	printf("12. Exit\n");
}