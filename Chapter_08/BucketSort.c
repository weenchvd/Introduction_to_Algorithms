#include "BucketSort.h"
#include "BucketSort_struct.h"
#include <stdlib.h>
#include <stdio.h>

void BucketSort(double* a, int size)
{
	DFloatLinkedList_t** b, ** p, * tmp, * node;
	int i, j, cond;
	if ((b = malloc(sizeof(DFloatLinkedList_t*) * size)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated (BucketSort()) |\n");
		return;
	}
	for (i = 0; i < size; i++) {
		b[i] = NULL;
	}
	for (i = 0; i < size; i++) {
		if ((tmp = malloc(sizeof(DFloatLinkedList_t))) == NULL) {
			printf("\n\n\t| ERROR | Memory allocator error. No memory allocated (BucketSort()) |\n");
			return;
		}
		tmp->num = a[i];
		tmp->next = NULL;
		if (*(p = b + (int)(size * a[i])) == NULL) {
			*p = tmp;
		}
		else {
			node = *p;
			while (TRUE) {
				if (node->next == NULL) {
					node->next = tmp;
					break;
				}
				else {
					node = node->next;
				}
			}
		}
	}
	for (i = 0; i < size; i++) {
		if (b[i] != NULL && b[i]->next != NULL) {
			tmp = b[i]->next;
			b[i]->next = NULL;
			for (cond = TRUE; cond;) {
				p = b + i;
				node = tmp;
				if ((tmp = tmp->next) == NULL) {
					cond = FALSE;
				}
				node->next = NULL;
				while (TRUE) {
					if (node->num <= (*p)->num) {
						node->next = *p;
						*p = node;
						break;
					}
					else if ((*p)->next == NULL) {
						(*p)->next = node;
						break;
					}
					else {
						p = &((*p)->next);
					}
				}
			}
		}
	}
	for (i = 0, j = 0; i < size; i++) {
		if (b[i] != NULL) {
			node = b[i];
			while (TRUE) {
				a[j++] = node->num;
				tmp = node;
				node = node->next;
				free(tmp);
				if (node == NULL) {
					break;
				}
			}
		}
	}
	free(b);
	return;
}