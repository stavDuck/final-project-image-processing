#ifndef __FINAL_PROJECT_H
#define __FINAL_PROJECT_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAGIC_NUMBER 1
#define COLS 2
#define ROWS 3
#define DEPTH 4
#define SIZE_OF_RGB 3
#define IMAGE_TYPE_SIZE 3
#define PPM_TYPE "ppm"
#define PGM_TYPE "pgm"
#define P2_FORMAT "P2"
#define P3_FORMAT "P3"
#define P5_FORMAT "P5"
#define P6_FORMAT "P6"
#define K2 2
#define K3 3
#define K4 4
#define BLACK 0
#define WHITE 1
#define BYTE_LENGTH 8
#define MAX_PIXEL_VALUE 255

typedef struct tnode TNODE;
typedef struct tnode_lnode TNODE_LNODE;
typedef struct tnode_list TNODE_LIST;

typedef struct rgb {
	unsigned char r, g, b;
}RGB;

typedef unsigned short IMG_POS[2];

typedef struct tnode_lnode {
	TNODE* node;
	struct tnode_lnode* next;
}TNODE_LNODE;

typedef struct tnode_list {
	TNODE_LNODE* head;
	TNODE_LNODE* tail;
}TNODE_LIST;

typedef struct tnode {
	IMG_POS position;
	TNODE_LIST nextPossiblePositions;
}TNODE;

typedef struct segment {
	TNODE* root;
}SEGMENT;

typedef struct colorImage {
	unsigned short rows, cols;
	RGB** pixels;
}COLOR_IMAGE;

typedef struct grayImage {
	unsigned short rows, cols;
	unsigned char** pixels;
}GRAY_IMAGE;

typedef struct img_pos_node {
	IMG_POS position;
	struct img_pos_node* next, * prev;
}IMG_POS_NODE;

typedef struct img_pos_list {
	IMG_POS_NODE* head;
	IMG_POS_NODE* tail;
}IMG_POS_LIST;


// functions 1
COLOR_IMAGE* readPPM(char* fname);
void getHeaderPPMData(FILE* fp, COLOR_IMAGE* image);
void getBodyPPMData(FILE* fp, COLOR_IMAGE* image);
void setHeaderPPMValuesToImage(FILE* fp, COLOR_IMAGE* image, int saveDataInd);
void checkFileOpening(FILE* fp);
void skipComment(FILE* fp);

// functions 2
GRAY_IMAGE* readPGM(char* fname);
void getBodyPGMData(FILE* fp, GRAY_IMAGE* image);
void getHeaderPGMData(FILE* fp, GRAY_IMAGE* image);
void setHeaderPGMValuesToImage(FILE* fp, GRAY_IMAGE* image, int saveDataInd);

//functions 3+4
SEGMENT findSingleSegment(GRAY_IMAGE* img, IMG_POS start, unsigned char threshold);
TNODE_LIST findSingleSegmentHelper(GRAY_IMAGE* img, bool** flagArray, IMG_POS originalStart, IMG_POS start, unsigned char threshold);
bool** boolianHelperArray(int rows, int cols);
bool checkNeighborValid(GRAY_IMAGE* img, IMG_POS start, short x, short y, unsigned char threshold);
TNODE_LIST listValidPosition(GRAY_IMAGE* img, bool** flagArray, IMG_POS originalStart, IMG_POS start, unsigned char threshold);
bool checkThreshold(GRAY_IMAGE* img, IMG_POS start, short x, short y, unsigned char threshold);
void makeEmptyList(TNODE_LIST* lst);
TNODE_LNODE* createNewListNode(TNODE* node, TNODE_LNODE* next);
void insertDataToEndList(TNODE_LIST* lst, TNODE* node);
void insertNodeToEndList(TNODE_LIST* lst, TNODE_LNODE* tail);
void makeEmptyTreeList(TNODE_LIST* lst);
TNODE* createNewTreeNode(short x, short y);
void freeBoolArray(bool** arr, int rows);
int findAllSegments(GRAY_IMAGE* img, unsigned char threshold, IMG_POS_LIST** segments);
IMG_POS_LIST createImagePositionListFromSingleSegment(SEGMENT* segment, bool** flagArray);
void createImagePositionListFromSingleSegmentHelper(TNODE* root, bool** flagArray, IMG_POS_LIST* newList);
void checkAllocation(void* lst);
void makeEmptyPositionList(IMG_POS_LIST* lst);
IMG_POS_NODE* createNewListPositionNode(IMG_POS position, IMG_POS_NODE* next, IMG_POS_NODE* prev);
void insertDataToEndPositionList(IMG_POS_LIST* lst, IMG_POS position);
void insertNodeToEndPositionList(IMG_POS_LIST* lst, IMG_POS_NODE* tail);

//question 5
GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments, unsigned int size);
void fillGrayImagePixels(GRAY_IMAGE* image, IMG_POS_LIST* segments, unsigned int size);
void allocateGrayImagePixelArr(GRAY_IMAGE* image);
void getMaxFromSegmentList(IMG_POS_LIST* segment, unsigned int size, int* x, int* y);

//question 6
void saveCompressed(char* fname, GRAY_IMAGE* image, unsigned char maxGrayLevel);
void setCompressedHeader(FILE* fp, GRAY_IMAGE* grayImage, unsigned char maxGrayLevel);
int getLengthZipByte(unsigned char newMaxGrey);
int calculatePrevAndCurrBytes(unsigned char* prevByte, unsigned char* currByte, int lengthZipByte, int prevRemind, bool* extraSpaceInPrev);

//question 7
void convertCompressedImageToPGM(char* fname);
void getHeaderDataFromCompressedFile(FILE* compressedFile, int* rows, int* cols, unsigned char* maxGrayLevel);
int calculatePrevAndCurrCompressed(unsigned char* prevByte, unsigned char* currByte, int numOfBits, int lengthPrev);

//question 8
void convertPPMToPGM(char* fname);
void writePGMFileFromPPMImage(FILE* grayFile, COLOR_IMAGE* colorImage, int depth, bool isFileBinary);
int getImageDepth(FILE* fp);
void writeImageHeader(FILE* imageFile, char* imageType, int cols, int rows, int depth);
void writePGMImageBody(FILE* grayFile, COLOR_IMAGE* colorImage);
int convertColorPixelToGrayPixel(RGB pixel);
void scanHeaderDataToFindDepth(FILE* fp, int saveDataInd, int* depth);
char* createNewFileName(char* fname, char* endingStr);

// question 9
void convertPGMToBW(char* fname);
void writeBlackWhiteBodyFromPGM(FILE* fp, GRAY_IMAGE* grayImage, int k, int depth);
int calculateBlackWhiteIndex(int k, int indexPixel, int row, int col);
char* createBlackWhiteFileName(char* fname, int k);

// question 10
COLOR_IMAGE* readPPM_Binary(char* fname);
void getBodyPPMData_Binary(FILE* fp, COLOR_IMAGE* image);
void convertPPMToPGM_Bin(char* fname);
void writePGMImageBody_Binary(FILE* grayFile, COLOR_IMAGE* colorImage);

// question 11
void convertPGMToBW_Bin(char* fname);
void writeBlackWhiteBodyFromPGM_Binary(FILE* fp, GRAY_IMAGE* grayImage, int k, int depth);
GRAY_IMAGE* readPGM_Binary(char* fname);
void getBodyPGMData_Binary(FILE* fp, GRAY_IMAGE* image);

// question 12
void menu();
bool checkValidInput(int num);
void printMenu();
void activateUsersChoice();
void freeGrayImage(GRAY_IMAGE* image);
void freeColorImage(COLOR_IMAGE* image);
char* getFileNameFromUser();
bool checkIfFileExists(char* fname);
void createANewPGMFormatP2File(GRAY_IMAGE* image);
int checkIfUserEnteredEndingFile(char* name);
unsigned char getDepthFromGrayImage(GRAY_IMAGE* image);
void writePGMFileBodyFromGrayImage(FILE* grayFile, GRAY_IMAGE* grayImage);


#endif
