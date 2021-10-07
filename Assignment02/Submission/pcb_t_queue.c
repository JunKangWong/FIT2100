/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

pcb_t (fcfs) queue structure defined in stack.
*/

/*
This module is a simple queue(FCFS) implementation implemeted in stack memory.
*/

#include "pcb_t_queue.h"


/*
Given input, this function enqueue/inserts item into the queue and increments the rear pointer.

Argument: 
Queue *q: Queue which items were to be inserted into.
pcc_t input: item to be inserted into the Queue.

*/
void enqueue(Queue *q, pcb_t input){
	q->item_count ++;
	q->value[++q->rear] = input;
}



/*
Given the queue object, this function dequeue/pops the item at the front of the queue, then
increment the front pointer.

Argument:
Queue *q: Queue where the front object is to be extracted.
*/
pcb_t dequeue(Queue *q){
	q->item_count--;
	return q->value[++q->front];
}



/*
Given a declared Queue address, this function initialise the Queue into initial setups.
*/
void initialise_queue(Queue *q){
	q->front = -1;
	q->rear = -1;
	q->item_count = 0;
}
