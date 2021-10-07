/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

header file of pcb_t_queue.c
*/
#define MAX_SIZE 100


typedef struct queue{
	pcb_t value[MAX_SIZE];
	int front;
	int rear;
	int item_count;
} Queue;


/*Function prototype*/
void enqueue(Queue *q, pcb_t input);
pcb_t dequeue(Queue *q);
void initialise_queue(Queue *q);
