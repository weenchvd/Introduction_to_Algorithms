#ifndef _STRUCT_H
#define _STRUCT_H

#define SSTACKSIZE 100

typedef struct Sequence {
	char* s;					// string
	int size;					// string length
} Sequence_t;

typedef struct SequenceSet {
	char* sstack[SSTACKSIZE];
	int sp;
} SSet_t;

#endif