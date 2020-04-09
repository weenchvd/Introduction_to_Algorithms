#ifndef _COMMON_H
#define _COMMON_H

#define DEBUG 1
#define ARRAYSTARTINDEX 0

#define FIRSTVERTEXNUMBER 1					/* difference between the first array number and the first vertex number */

enum ReturnTypeCommon { FAILURE = -1, SUCCESS, EXITWITHSUCCESS };

enum GraphType { DIRECTED = 1, UNDIRECTED };
enum GraphVertexColor { NOCOLOR = 0, WHITE, GRAY, BLACK };

#endif