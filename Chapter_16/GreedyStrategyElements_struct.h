#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct KnapsackAUXTables {
	int* v;			/* Value table */
	int* w;			/* Weight table */
	int* s;			/* Solution table */
} KATables_t;

typedef struct KnapsackItems {
	int* v;			/* Values */
	int* w;			/* Weights */
	int n;			/* Number of items */
	int maxw;		/* Maximum weight */
} KI_t;

#endif