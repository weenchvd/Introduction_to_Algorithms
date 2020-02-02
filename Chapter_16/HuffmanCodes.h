#ifndef _HUFFMANCODES_H
#define _HUFFMANCODES_H

#include "HuffmanCodes_common.h"
#include "HuffmanCodes_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HEAPPARENT(i) (i >> 1)
#define HEAPLEFTCHILD(i) (i << 1)
#define HEAPRIGHTCHILD(i) (i << 1 | 1)
#define FBTINTERNALNODE -1
#define ENDOFSYMBOLCODE -1

enum DirectionType { LEFTDIR, RIGHTDIR };

int ParseFilename(FNSet_t* fn, char* argv);
int CompressFile(FILE* fo, FILE* fw);
int DecompressFile(FILE* fo, FILE* fw);
void BuildAlphabet(FILE* fo, Alphabet_t* alph);
FBT_t* BuildHuffmanCode(FBTHeapQueue_t* queue);
FBT_t* CreateFBTNode(int freq, int symbol);
int WalkThroughTree(FILE* fw, Alphabet_t* alph, FBT_t* root, SymbolCode_t* symcode);
int EncodeSymbols(FILE* fo, FILE* fw, SymbolCode_t* symcode);
void FreeFBTNode(FBT_t* root);
void InitializeHeap(FBTHeapQueue_t* queue);
void BuildMinHeap(FBTHeapQueue_t* queue, Alphabet_t* alph);
FBTHeapQueue_t* HeapExtractMin(FBTHeapQueue_t* queue);
void MinHeapInsert(FBTHeapQueue_t* queue, FBT_t* node);
void HeapDecreaseKey(FBTHeapQueue_t* queue, int index, int freq);
void MinHeapify(FBTHeapQueue_t* queue, int index);
int ParseFileHeader(FILE* fo, FileHeader_t* fh);
FBT_t* ReconstructHuffmanCode(FileHeader_t* fh);
int DecodeSymbols(FILE* fo, FILE* fw, FileHeader_t* fh, FBT_t* root);

#endif