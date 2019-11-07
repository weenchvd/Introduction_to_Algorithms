#include "PointersObjects.h"

void PutAllObjectsOnFreeList(ObjectSet_t* set)
{
	int i, object;
	set->free = set->head = NIL;
	for (i = OBJECTSETSIZE - 1; i >= ARRAYSTARTINDEX; i--) {
		set->next[i] = NIL;
		set->prev[i] = NIL;
		FreeObject(set, i);
	}
	return;
}

int PutObjectOnLinkedList(ObjectSet_t* set, int object, int key)
{
	if (object != FAILURE) {
		if (set->head == NIL) {
			set->next[object] = NIL;
		}
		else {
			set->next[object] = set->head;
			set->prev[set->head] = object;
		}
		set->key[object] = key;
		set->prev[object] = NIL;
		set->head = object;
		return SUCCESS;
	}
	return FAILURE;
}

int AllocateObject(ObjectSet_t* set)
{
	int object;
	if (set->free == NIL) {
		printf("\n\n\t| ERROR | Out of space |\n");
		object = FAILURE;
	}
	else {
		object = set->free;
		set->free = set->next[object];
	}
	return object;
}

void FreeObject(ObjectSet_t* set, int object)
{
	if (set->prev[object] != NIL && set->next[object] != NIL) {
		set->next[set->prev[object]] = set->next[object];
		set->prev[set->next[object]] = set->prev[object];
	}
	else if (set->prev[object] != NIL && set->next[object] == NIL) {
		set->next[set->prev[object]] = NIL;
	}
	else if (set->prev[object] == NIL && set->next[object] != NIL) {
		set->prev[set->next[object]] = NIL;
		set->head = set->next[object];
	}
	else {
		set->head = NIL;
	}
	set->next[object] = set->free;
	set->free = object;
	return;
}

void CompactifyList(ObjectSet_t* set)
{
	int l;									/* an object in the linked list to swap */
	int f;									/* an object in the free list to swap */
	int m;
	FreeSet_t freeset;
	if (set->head == NIL || set->free == NIL) {
		return;
	}
	for (m = 0, l = set->head; l != NIL; m++, l = set->next[l]);
	l = set->head;
	f = set->free;
	freeset.previous = NIL;
	while (l != NIL) {
		if (l < m) {
			l = set->next[l];
			continue;
		}
		for (; f >= m; f = set->next[f]) {
			freeset.previous = f;
		}
		if (f == NIL) {
			printf("\n\n\t| ERROR | Free list is empty |\n");
			break;
		}
		freeset.nextfield = set->next[f];
		set->next[f] = set->next[l];
		set->key[f] = set->key[l];
		set->prev[f] = set->prev[l];
		if (set->prev[f] != NIL && set->next[f] != NIL) {
			set->prev[set->next[f]] = f;
			set->next[set->prev[f]] = f;
		}
		else if (set->prev[f] != NIL && set->next[f] == NIL) {
			set->next[set->prev[f]] = f;
		}
		else if (set->prev[f] == NIL && set->next[f] != NIL) {
			set->prev[set->next[f]] = f;
			set->head = f;
		}
		else {
			set->head = f;
		}
		if (freeset.previous != NIL) {
			set->next[freeset.previous] = l;
		}
		else {
			set->free = l;
		}
		set->next[l] = freeset.nextfield;
		freeset.nextfield = l;
		l = set->next[f];
		freeset.previous = freeset.nextfield;
		f = set->next[freeset.nextfield];
	}
	return;
}

void PrintSet(ObjectSet_t* set)
{
	int object;
	printf("Linked List\n");
	for (object = set->head; object != NIL; object = set->next[object]) {
		printf("\tObject # %2d: key %6d, next %2d, prev %2d\n",
			object, set->key[object], set->next[object], set->prev[object]);
	}
	printf("Free List\n");
	for (object = set->free; object != NIL; object = set->next[object]) {
		printf("\tObject # %2d: next %2d\n", object, set->next[object]);
	}
	return;
}