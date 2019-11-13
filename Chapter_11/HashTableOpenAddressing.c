#include "HashTableOpenAddressing.h"

/* Double hashing */
int HashInsert(int* ht, int key)
{
	int i, j;
	i = 0;
	do {
		j = HASH(key, i);
		if (ht[j] < 0) {					/* ht[j] == NIL || ht[j] == DELETED */
			ht[j] = key;
			return j;
		}
		i++;
	} while (i < HASHTABLESIZE);
	printf("\n\n\t| ERROR | Hash table overflow |\n");
	return FAILURE;
}

int HashSearch(int* ht, int key)
{
	int i, j;
	i = 0;
	do {
		j = HASH(key, i);
		if (ht[j] == key) {
			return j;
		}
		i++;
	} while (ht[j] != NIL && i < HASHTABLESIZE);
	return FAILURE;
}

int HashDelete(int* ht, int key)
{
	int i, j;
	i = 0;
	do {
		j = HASH(key, i);
		if (ht[j] == key) {
			ht[j] = DELETED;
			return j;
		}
		i++;
	} while (ht[j] != NIL && i < HASHTABLESIZE);
	return FAILURE;
}

void HashPrint(int* ht, int size)
{
	int i, printdl, cond;
	char* dashline1 = " --------------------------- \n";
	char* dashline2 = "|---------------------------|\n";
	printdl = FALSE;
	cond = FALSE;
	printf("%s", dashline1);
	for (i = 0; i < size; i++) {
		if (ht[i] >= 0) {
			if (printdl) {
				printf("%s", dashline2);
				printdl = FALSE;
			}
			printf("| #%5d | Key %12d |\n", i, ht[i]);
			cond = TRUE;
		}
		else if (cond) {
			printdl = TRUE;
		}
	}
	printf("%s", dashline1);
	return;
}