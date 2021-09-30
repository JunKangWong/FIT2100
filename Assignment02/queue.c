#include <stdio.h>

#define MAX_SIZE 100
#define PROCESS_NAME_SIZE 11	// assume name of process is never more than 10 characters in length and does not contain spaces
#define START_TIME 0

/*Special enumerated data type for process state*/
typedef enum {
	READY, RUNNING, EXIT
}process_state_t;


typedef struct {
	char process_name[PROCESS_NAME_SIZE]; // A string that identifies the process
	
	/*Time are measured in seconds*/
	int entryTime;				// The time process entered system
	int serviceTime;			// The total CPU time required by the process
	int remainingTime;			// Remaining service time until completion
	process_state_t state;		// current process state (e.g. READY) as specified in the enum above

}pcb_t;


typedef struct queue{
	pcb_t value[MAX_SIZE];
	int front;
	int rear;
	int item_count;
} Queue;


void enqueue(Queue *q, pcb_t input){
	q->item_count ++;
	q->value[++q->rear] = input;
}

pcb_t dequeue(Queue *q){
	q->item_count--;
	return q->value[++q->front];;
}

void initialise_queue(Queue *q){
	q->front = -1;
	q->rear = -1;
	q->item_count = 0;
}

/*
int main(){
	int i;
	Queue q;
	initialise_queue(&q);
	
	pcb_t process1;
	process1.entryTime = 1;
	process1.serviceTime = 2;
	process1.remainingTime = 3;
	process1.state = READY;
	
	pcb_t process2;
	process2.entryTime = 4;
	process2.serviceTime = 5;
	process2.remainingTime = 6;
	process2.state = RUNNING;
	
	enqueue(&q, process1);
	enqueue(&q, process2);
	
	int count = q.item_count;
	
	for(i = 0; i < count; i++){
		pcb_t current_process = dequeue(&q);
		printf("%d\n", current_process.entryTime);
	}

	
	return 0;
}
*/
