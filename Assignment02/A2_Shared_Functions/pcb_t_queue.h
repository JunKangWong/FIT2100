//#include "process_structure.h"

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
