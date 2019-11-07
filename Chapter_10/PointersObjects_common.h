#ifndef _COMMON_H
#define _COMMON_H

#define DEBUG 0
#define ARRAYSTARTINDEX 0

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };
enum Boolean { FALSE, TRUE };

enum FreeListType { NIL = ARRAYSTARTINDEX - 1 };

#endif