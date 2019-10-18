#include "HeapPriorityQueue.h"

int heapsize;
int heapsizelimit;
PriorityQueue_t queue;

void InitializeHeap(void)
{
	heapsize = 0;
	heapsizelimit = PRIORITYQUEUESIZE - FIRSTITEMOFARRAY;
	return;
}

Handle_t* HeapMax(Handle_t* set)
{
	if (heapsize < 1) {
		printf("\n\n\t| ERROR | Heap underflow |\n");
		return NULL;
	}
	set->priority = HEAPMAXIMUM(queue.priority);
	set->handle = HEAPMAXIMUM(queue.handle);
	return set;
}

Handle_t* HeapExtractMax(Handle_t* set)
{
	if (heapsize < 1) {
		printf("\n\n\t| ERROR | Heap underflow |\n");
		return NULL;
	}
	set->priority = queue.priority[FIRSTITEMOFARRAY];
	set->handle = queue.handle[FIRSTITEMOFARRAY];
	queue.priority[FIRSTITEMOFARRAY] = queue.priority[heapsize];
	queue.handle[FIRSTITEMOFARRAY] = queue.handle[heapsize--];
	MaxHeapify(FIRSTITEMOFARRAY);
	return set;
}

void HeapIncreaseKey(int index, int key)
{
	int handle, parent;
	if (index > heapsize) {
		printf("\n\n\t| ERROR | Index is greater than heap size |\n");
		return;
	}
	if (index < FIRSTITEMOFARRAY) {
		printf("\n\n\t| ERROR | Index is less than %d |\n", FIRSTITEMOFARRAY);
		return;
	}
	if (key < queue.priority[index]) {
		printf("\n\n\t| ERROR | New key is smaller than current key |\n");
		return;
	}
	handle = queue.handle[index];
	while (index > 1 && queue.priority[parent = PARENT(index)] < key) {
		queue.priority[index] = queue.priority[parent];
		queue.handle[index] = queue.handle[parent];
		index = parent;
	}
	queue.priority[index] = key;
	queue.handle[index] = handle;
	return;
}

void MaxHeapInsert(int key, int handle)
{
	if (heapsize >= heapsizelimit) {
		printf("\n\n\t| ERROR | Heap size limit reached |\n");
		return;
	}
	queue.priority[++heapsize] = INT_MIN;
	queue.handle[heapsize] = handle;
	HeapIncreaseKey(heapsize, key);
	return;
}

void MaxHeapDelete(int index)
{
	if (index > heapsize) {
		printf("\n\n\t| ERROR | Index is greater than heap size |\n");
		return;
	}
	if (index < FIRSTITEMOFARRAY) {
		printf("\n\n\t| ERROR | Index is less than %d |\n", FIRSTITEMOFARRAY);
		return;
	}
	queue.priority[index] = queue.priority[heapsize];
	queue.handle[index] = queue.handle[heapsize--];
	MaxHeapify(index);
	return;
}

void MaxHeapify(int index)
{
	int left, right, largest;
	Handle_t tmp;
	while (TRUE)
	{
		left = LEFT(index);
		right = RIGHT(index);
		if (left <= heapsize && queue.priority[left] > queue.priority[index]) {
			largest = left;
		}
		else {
			largest = index;
		}
		if (right <= heapsize && queue.priority[right] > queue.priority[largest]) {
			largest = right;
		}
		if (largest != index) {
			tmp.priority = queue.priority[index];
			tmp.handle = queue.handle[index];
			queue.priority[index] = queue.priority[largest];
			queue.handle[index] = queue.handle[largest];
			queue.priority[largest] = tmp.priority;
			queue.handle[largest] = tmp.handle;
			index = largest;
		}
		else {
			break;
		}
	}
	return;
}

Handle_t* HeapMin(Handle_t* set)
{
	if (heapsize < 1) {
		printf("\n\n\t| ERROR | Heap underflow |\n");
		return NULL;
	}
	set->priority = HEAPMINIMUM(queue.priority);
	set->handle = HEAPMINIMUM(queue.handle);
	return set;
}

Handle_t* HeapExtractMin(Handle_t* set)
{
	if (heapsize < 1) {
		printf("\n\n\t| ERROR | Heap underflow |\n");
		return NULL;
	}
	set->priority = queue.priority[FIRSTITEMOFARRAY];
	set->handle = queue.handle[FIRSTITEMOFARRAY];
	queue.priority[FIRSTITEMOFARRAY] = queue.priority[heapsize];
	queue.handle[FIRSTITEMOFARRAY] = queue.handle[heapsize--];
	MinHeapify(FIRSTITEMOFARRAY);
	return set;
}

void HeapDecreaseKey(int index, int key)
{
	int handle, parent;
	if (index > heapsize) {
		printf("\n\n\t| ERROR | Index is greater than heap size |\n");
		return;
	}
	if (index < FIRSTITEMOFARRAY) {
		printf("\n\n\t| ERROR | Index is less than %d |\n", FIRSTITEMOFARRAY);
		return;
	}
	if (key > queue.priority[index]) {
		printf("\n\n\t| ERROR | New key is bigger than current key |\n");
		return;
	}
	handle = queue.handle[index];
	while (index > 1 && queue.priority[parent = PARENT(index)] > key) {
		queue.priority[index] = queue.priority[parent];
		queue.handle[index] = queue.handle[parent];
		index = parent;
	}
	queue.priority[index] = key;
	queue.handle[index] = handle;
	return;
}

void MinHeapInsert(int key, int handle)
{
	if (heapsize >= heapsizelimit) {
		printf("\n\n\t| ERROR | Heap size limit reached |\n");
		return;
	}
	queue.priority[++heapsize] = INT_MAX;
	queue.handle[heapsize] = handle;
	HeapDecreaseKey(heapsize, key);
	return;
}

void MinHeapDelete(int index)
{
	if (index > heapsize) {
		printf("\n\n\t| ERROR | Index is greater than heap size |\n");
		return;
	}
	if (index < FIRSTITEMOFARRAY) {
		printf("\n\n\t| ERROR | Index is less than %d |\n", FIRSTITEMOFARRAY);
		return;
	}
	queue.priority[index] = queue.priority[heapsize];
	queue.handle[index] = queue.handle[heapsize--];
	MinHeapify(index);
	return;
}

void MinHeapify(int index)
{
	int left, right, smallest;
	Handle_t tmp;
	while (TRUE)
	{
		left = LEFT(index);
		right = RIGHT(index);
		if (left <= heapsize && queue.priority[left] < queue.priority[index]) {
			smallest = left;
		}
		else {
			smallest = index;
		}
		if (right <= heapsize && queue.priority[right] < queue.priority[smallest]) {
			smallest = right;
		}
		if (smallest != index) {
			tmp.priority = queue.priority[index];
			tmp.handle = queue.handle[index];
			queue.priority[index] = queue.priority[smallest];
			queue.handle[index] = queue.handle[smallest];
			queue.priority[smallest] = tmp.priority;
			queue.handle[smallest] = tmp.handle;
			index = smallest;
		}
		else {
			break;
		}
	}
	return;
}

void PrintQueue()
{
	int i;
	if (heapsize < 1) {
		printf("\nQueue is empty\n");
		return;
	}
	printf("\nPriority queue \"KEY, HANDLE\":\n");
	for (i = FIRSTITEMOFARRAY; i <= heapsize; i++) {
		printf("%13s%6d, %-6d\n", "", queue.priority[i], queue.handle[i]);
	}
	putchar('\n');
	return;
}