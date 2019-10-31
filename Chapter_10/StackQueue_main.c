/* Chapter 10.1 | Stack-Queue */

#include "StackQueue_common.h"
#include "StackQueue_struct.h"
#include <stdio.h>
#include <stdlib.h>

int StackEmpty(StackSet_t* s);
void Push(StackSet_t* s, int x);
int Pop(StackSet_t* s);
void Enqueue(QueueSet_t* q, int x);
int Dequeue(QueueSet_t* q);

int main(void)
{
	int number, action;
	StackSet_t s;
	QueueSet_t q;
	s.top = q.head = q.tail = ARRAYSTARTINDEX;
	printf("List of action:\n\t1 (Push), 2 (Pop), 3 (Enqueue), 4 (Dequeue)\n\n");
	while (TRUE) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case 1:
			printf("Please enter a number: ");
			if (scanf("%d", &number) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			Push(&s, number);
			break;
		case 2:
			printf("Number: %d\n", Pop(&s));
			break;
		case 3:
			printf("Please enter a number: ");
			if (scanf("%d", &number) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			Enqueue(&q, number);
			break;
		case 4:
			printf("Number: %d\n", Dequeue(&q));
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}