#ifndef _COMMON_H
#define _COMMON_H

#define DEBUG 1
#define FIRSTITEMOFARRAY 0

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };
enum Boolean { FALSE, TRUE };

typedef struct MiddleSet {
	int first;
	int last;
} MiddleSet_t;

#endif