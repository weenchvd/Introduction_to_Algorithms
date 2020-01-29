#ifndef _COMMON_H
#define _COMMON_H

#define DEBUG 0
#define ARRAYSTARTINDEX 0
#define HEAPSTARTINDEX 1
#define BUFFERSIZE 4096
#define ALPHABETSIZE 128

enum NodeType { INTERNALNODE, LEAFNODE };
//enum BitField { BIT1 = 1, BIT2 = 2, BIT3 = 4, BIT4 = 8, BIT5 = 16, BIT6 = 32, BIT7 = 64, BIT8 = 128 };
enum ReturnTypeCommon { FAILURE = -1, SUCCESS, EXITWITHSUCCESS };
enum Boolean { FALSE, TRUE };

#endif