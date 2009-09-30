#ifndef COMMONC_H_
#define COMMONC_H_

#include <stdio.h>
#include "fastCMaths.h"
#include "hashTableC.h"

//utils functions

//logging and debugging
#define DEBUG TRUE

#define LOGGING_OFF 0
#define LOGGING_INFO 1
#define LOGGING_DEBUG 2

extern int32_t LOG_LEVEL;

void setLogLevel(int32_t);

void logInfo(const char *string, ...);

void logDebug(const char *string, ...);

void uglyf(const char *string, ...);

int32_t systemLocal(const char *string, ...);

//memory
struct Chunks {
    struct List *chunkList;
    void * chunk;
    int32_t remaining;
    int32_t chunkSize;
    int32_t elementSize;
};

struct Chunks *constructChunks(int32_t chunkSize, int32_t elementSize);

void destructChunks(struct Chunks *);

void *mallocChunk(struct Chunks *chunk);

void *mallocLocal(int32_t i);

void *callocLocal(int32_t i, int32_t j);

//general data structures you always need
//lists
struct List {
    int32_t length;
    int32_t maxLength;
    void **list;
    void (*destructElement)(void *);
};

void listAppend(struct List *list, void *i);

void *listRemoveFirst(struct List *list);

void *arrayResize(void *current, int32_t *currentSize, int32_t newSize, int32_t base);

void listIntersection(struct List *list, struct List *list2, struct List *list3);

void listResize(struct List *list, int32_t newMaxSize);

int32_t listGetInt(struct List *list, int32_t index);

float listGetFloat(struct List *list, int32_t index);

void listReverse(struct List *list);

int32_t listContains(struct List *list, void *k);

void listRemove(struct List *list, void *k);

void listRemoveDuplicates(struct List *list);

int32_t listContainsDuplicates(struct List *list);

void *arrayCopyResize(void *current, int32_t *currentSize, int32_t newSize, int32_t base);

void *arrayPrepareAppend(void *current, int32_t *maxLength, int32_t currentLength, int32_t base);

void listCopyResize(struct List *list, int32_t newMaxSize);

struct List *listCopy(struct List *list);

void swapListFields(struct List *list1, struct List *list2);

struct List *cloneList(struct List *source);

void copyList(struct List *from, struct List *to);

struct hashtable *intListToHash(struct List *list, int32_t *(*getKey)(void *));

//list functions
struct List *copyConstructList(void **list, int32_t length, void (*destructElement)(void *));

struct List *constructZeroLengthList(int32_t length, void (*destructElement)(void *));

struct List *constructEmptyList(int32_t length, void (*destructElement)(void *));

void destructList(struct List *list);

void listAppendArray(struct List *list, void **array, int32_t length);

//int lists
struct IntList {
    int32_t length;
    int32_t maxLength;
    int32_t *list;
};

struct IntList *constructEmptyIntList(int32_t length);

void destructIntList(struct IntList *intList);

void intListAppend(struct IntList *intList, int32_t);

//ints
int32_t *constructInt(int32_t i);

void destructInt(int32_t *i);

int32_t *constructChunkInt(int32_t intValue, struct Chunks *chunks);

int64_t *constructChunkLong(int64_t longValue, struct Chunks *chunks);
//ints
int64_t *constructLong(int64_t i);

void destructLong(int64_t *i);

float *constructFloat(float i);

void destructFloat(float *i);

uint32_t hashtable_stringHashKey( void *k );

int32_t hashtable_stringEqualKey( void *key1, void *key2 );

uint32_t hashtable_intHashKey( void *k );

int32_t hashtable_intEqualKey( void *key1, void *key2 );

uint32_t hashtable_key( void *k );

int32_t hashtable_equalKey( void *key1, void *key2 );

uint32_t hashtable_intPairHashKey( void *k );

int32_t hashtable_intPairEqualKey( void *key1, void *key2 );

uint32_t hashtable_orderedIntPairHashKey( void *k );

int32_t hashtable_orderedIntPairEqualKey( void *key1, void *key2 );

int32_t *constructIntPair(int32_t i, int32_t j);

void destructIntPair(int32_t *i);

uint32_t hashtable_longHashKey( void *k );

int32_t hashtable_longEqualKey( void *key1, void *key2 );

int32_t intComparator(int32_t *i, int32_t *j);

int32_t longComparator(int64_t *i, int64_t *j);

int intComparator_Int(int32_t *i, int32_t *j);

int longComparator_Int(int64_t *i, int64_t *j);

int32_t intsComparator(int32_t *ints1, int32_t *ints2, int32_t length);

struct TraversalID {
    //tree traversal numbers, used as nodeIDs for identifying
    //orders in the tree
    //pre == pre order traversal
    //preEnd == max pre index + 1 of node in subtree
    //mid == mid order (in-order) traversal number
    //def __init__(self, pre, preEnd, mid):
    int32_t midStart;
    int32_t mid;
    int32_t midEnd;
    int32_t leafNo;
};

struct TraversalID *constructTraversalID(int32_t midStart, int32_t mid, int32_t midEnd, int32_t leafNo);

void destructTraversalID(struct TraversalID *traversalID);

struct BinaryTree {
    float distance;
    int32_t internal;
    struct TraversalID *traversalID;
    struct BinaryTree *left;
    struct BinaryTree *right;
};

int32_t leftMostLeafNo(struct TraversalID *traversalID);

int32_t rightMostLeafNo(struct TraversalID *traversalID);

int32_t leafNoInSubtree(struct TraversalID *traversalID);

struct BinaryTree *constructBinaryTree(float distance, int32_t internal,
                                              struct BinaryTree *left,
                                              struct BinaryTree *right);

void destructBinaryTree(struct BinaryTree *binaryTree);

void binaryTree_depthFirstNumbers(struct BinaryTree *binaryTree);

void printBinaryTree(FILE *file, struct BinaryTree *binaryTree, char **nodeNames);

void annotateTree(struct BinaryTree *bT, void *(*fn)(struct BinaryTree *i), struct List *list);

void getBinaryTreeNodesInMidOrder(struct BinaryTree *binaryTree, struct BinaryTree **labels);

float linOriginRegression(struct List *pointsX, struct List *pointsY);

/*
 * Copies a string, returning a string which must be cleaned up.
 */
char *stringCopy(const char *str);

/*
 * Joins two paths together, somewhat intelligently, to give one concatenated path.
 */
char *pathJoin(const char *pathPrefix, const char *pathSuffix);

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//temp files
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

int32_t constructRandomDir(const char *tempFilePath, char **tempDir);

int32_t destructRandomDir(char *tempDir);

void initialiseTempFileTree(char *rootDir, int32_t filesPerDir, int32_t levelNumber);

char *getTempFile();

void removeTempFile(char *tempFile);

void removeAllTempFiles();

struct TempFileTree {
	char *rootDir;
	int32_t filesPerDir;
	int32_t *levelsArray;
	int32_t levelNumber;
	int32_t tempFilesCreated;
	int32_t tempFilesDestroyed;
};

struct TempFileTree *constructTempFileTree(char *rootDir, int32_t filesPerDir, int32_t levelNumber);

void destructTempFileTree(struct TempFileTree *tempFileTree);

char *tempFileTree_getTempFile(struct TempFileTree *tempFileTree);

#endif /*COMMONC_H_*/
