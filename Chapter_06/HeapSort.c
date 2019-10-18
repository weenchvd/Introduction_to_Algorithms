#include "HeapSort.h"

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void HeapSortRecursive(int* a, int size, int type)
{
	if (type) {
		HeapSortNondecreasingOrderR(a, size);
	}
	else {
		HeapSortNonincreasingOrderR(a, size);
	}
	return;
}

void HeapSortNondecreasingOrderR(int* a, int size)
{
	int i, tmp;
	BuildMaxHeapR(a, size);
	for (i = size - 1; i > 0; i--) {
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		MaxHeapifyR(a, i, 0);
	}
	return;
}

void BuildMaxHeapR(int* a, int size)
{
	int i;
	for (i = (size >> 1) - 1; i >= 0; i--) {
		MaxHeapifyR(a, size, i);
	}
	return;
}

void MaxHeapifyR(int* a, int size, int index)
{
	int left, right, largest, tmp;
	left = LEFT(index);
	right = RIGHT(index);
	if (left < size && a[left] > a[index]) {
		largest = left;
	}
	else {
		largest = index;
	}
	if (right < size && a[right] > a[largest]) {
		largest = right;
	}
	if (largest != index) {
		tmp = a[index];
		a[index] = a[largest];
		a[largest] = tmp;
		MaxHeapifyR(a, size, largest);
	}
	return;
}

void HeapSortNonincreasingOrderR(int* a, int size)
{
	int i, tmp;
	BuildMinHeapR(a, size);
	for (i = size - 1; i > 0; i--) {
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		MinHeapifyR(a, i, 0);
	}
	return;
}

void BuildMinHeapR(int* a, int size)
{
	int i;
	for (i = (size >> 1) - 1; i >= 0; i--) {
		MinHeapifyR(a, size, i);
	}
	return;
}

void MinHeapifyR(int* a, int size, int index)
{
	int left, right, smallest, tmp;
	left = LEFT(index);
	right = RIGHT(index);
	if (left < size && a[left] < a[index]) {
		smallest = left;
	}
	else {
		smallest = index;
	}
	if (right < size && a[right] < a[smallest]) {
		smallest = right;
	}
	if (smallest != index) {
		tmp = a[index];
		a[index] = a[smallest];
		a[smallest] = tmp;
		MinHeapifyR(a, size, smallest);
	}
	return;
}


/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void HeapSortIterative(int* a, int size, int type)
{
	if (type) {
		HeapSortNondecreasingOrderI(a, size);
	}
	else {
		HeapSortNonincreasingOrderI(a, size);
	}
	return;
}

void HeapSortNondecreasingOrderI(int* a, int size)
{
	int i, tmp;
	BuildMaxHeapI(a, size);
	for (i = size - 1; i > 0; i--) {
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		MaxHeapifyI(a, i, 0);
	}
	return;
}

void BuildMaxHeapI(int* a, int size)
{
	int i;
	for (i = (size >> 1) - 1; i >= 0; i--) {
		MaxHeapifyI(a, size, i);
	}
	return;
}

void MaxHeapifyI(int* a, int size, int index)
{
	int left, right, largest, tmp;
	while (TRUE)
	{
		left = LEFT(index);
		right = RIGHT(index);
		if (left < size && a[left] > a[index]) {
			largest = left;
		}
		else {
			largest = index;
		}
		if (right < size && a[right] > a[largest]) {
			largest = right;
		}
		if (largest != index) {
			tmp = a[index];
			a[index] = a[largest];
			a[largest] = tmp;
			index = largest;
		}
		else {
			break;
		}
	}
	return;
}

void HeapSortNonincreasingOrderI(int* a, int size)
{
	int i, tmp;
	BuildMinHeapI(a, size);
	for (i = size - 1; i > 0; i--) {
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		MinHeapifyI(a, i, 0);
	}
	return;
}

void BuildMinHeapI(int* a, int size)
{
	int i;
	for (i = (size >> 1) - 1; i >= 0; i--) {
		MinHeapifyI(a, size, i);
	}
	return;
}

void MinHeapifyI(int* a, int size, int index)
{
	int left, right, smallest, tmp;
	while (TRUE)
	{
		left = LEFT(index);
		right = RIGHT(index);
		if (left < size && a[left] < a[index]) {
			smallest = left;
		}
		else {
			smallest = index;
		}
		if (right < size && a[right] < a[smallest]) {
			smallest = right;
		}
		if (smallest != index) {
			tmp = a[index];
			a[index] = a[smallest];
			a[smallest] = tmp;
			index = smallest;
		}
		else {
			break;
		}
	}
	return;
}