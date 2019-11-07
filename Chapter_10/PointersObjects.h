#ifndef _POINTERSOBJECTS_H
#define _POINTERSOBJECTS_H

#include "PointersObjects_common.h"
#include "PointersObjects_struct.h"
#include <stdio.h>
#include <stdlib.h>

void PutAllObjectsOnFreeList(ObjectSet_t* set);
int PutObjectOnLinkedList(ObjectSet_t* set, int object, int key);
int AllocateObject(ObjectSet_t* set);
void FreeObject(ObjectSet_t* set, int object);
void CompactifyList(ObjectSet_t* set);
void PrintSet(ObjectSet_t* set);

#endif