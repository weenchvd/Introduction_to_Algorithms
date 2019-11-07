/* Chapter 10.3 | Pointers-Objects */
/* Exercise 10.3-5 | Pointers-Objects */

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

int main(void)
{
	int action, key, object;
	ObjectSet_t oset;
	PutAllObjectsOnFreeList(&oset);
	printf("List of action:\n\t1 (PutAllObjectsOnFreeList), 2 (CompactifyList), 3 (AllocateObject & PutObjectOnLinkedList), 4 (FreeObject), "
		"5 (PrintSet)\n\n");
	while (TRUE) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case 1:
			PutAllObjectsOnFreeList(&oset);
			break;
		case 2:
			CompactifyList(&oset);
			break;
		case 3:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (PutObjectOnLinkedList(&oset, AllocateObject(&oset), key) == SUCCESS) {
				printf("PutObjectOnLinkedList(): done!\n");
			}
			break;
		case 4:
			printf("Please enter a object: ");
			if (scanf("%d", &object) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			FreeObject(&oset, object);
			break;
		case 5:
			PrintSet(&oset);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}