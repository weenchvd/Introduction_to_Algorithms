#ifndef _COMMON_H
#define _COMMON_H

#include <limits.h>

#define DEBUG 0
#define ARRAYSTARTINDEX 0
#define HEAPSTARTINDEX 1
#define BUFFERSIZE 4096
#define ALPHABETSIZE 128
#define OUTPUTFILEEXTENSION "z8"

enum OperationType { DECOMPRESSTXT, COMPRESSTXT };
enum NodeType { INTERNALNODE, LEAFNODE };
enum ReturnTypeCommon { FAILURE = -1, SUCCESS, EXITWITHSUCCESS };
enum Boolean { FALSE, TRUE };

#endif