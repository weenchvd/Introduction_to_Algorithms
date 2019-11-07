#ifndef _STRUCT_H
#define _STRUCT_H

#define OBJECTSETSIZE 10

typedef struct ObjectSet {
	int free;
	int head;
	int next[OBJECTSETSIZE];
	int key[OBJECTSETSIZE];
	int prev[OBJECTSETSIZE];
} ObjectSet_t;

typedef struct FreeSet {
	int previous;
	int nextfield;
} FreeSet_t;

#endif