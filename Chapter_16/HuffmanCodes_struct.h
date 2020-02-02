#ifndef _STRUCT_H
#define _STRUCT_H

#include "HuffmanCodes_common.h"

#define PATHNAMESIZE 256
#define EXTSIZE 4
#define FBTHEAPQUEUESIZE (2 * ALPHABETSIZE - 1) + HEAPSTARTINDEX

#if (2 * ALPHABETSIZE) % CHAR_BIT > 0
#define STRUCTURESIZE (2 * ALPHABETSIZE) / CHAR_BIT + 1
#else
#define STRUCTURESIZE (2 * ALPHABETSIZE) / CHAR_BIT
#endif

typedef struct FilenameSet {
	char pathname[PATHNAMESIZE];
	char ext[EXTSIZE];						/* .txt OR .z8 */
	char optype;							/* 1 - source, 0 - compressed */
} FNSet_t;

typedef struct Alphabet {
	unsigned int freq[ALPHABETSIZE];
	unsigned int totalsymbols;
	unsigned char uniquesymbols;
	char symbol[ALPHABETSIZE];
} Alphabet_t;

typedef struct SymbolCode {
	char* code[ALPHABETSIZE];
} SymbolCode_t;

typedef struct FileHeader {
	unsigned int totalsymbols;
	unsigned char uniquesymbols;
	char symbolsinorder[ALPHABETSIZE];
	char structure[STRUCTURESIZE];
} FileHeader_t;

typedef struct FullBinaryTree {
	struct FullBinaryTree* parent;
	struct FullBinaryTree* left;
	struct FullBinaryTree* right;
	unsigned int freq;
	char symbol;
} FBT_t;

typedef struct FBTHeapQueue {
	struct FullBinaryTree* node[FBTHEAPQUEUESIZE];
	int heapsize;							/* node[heapsize] - last node */
	int heapsizelimit;
} FBTHeapQueue_t;
 
#endif