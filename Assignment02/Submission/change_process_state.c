//#include "change_process_state.h"


bool schedule_process(Heap *ready, pcb_t *running_process, int current_time){
	// update firstServedTime only when remainingTime equals to firstServedTime.
	*running_process = extract_root(ready);
	running_process->firstServedTime = (running_process->remainingTime == running_process->serviceTime) ?
	current_time : running_process->firstServedTime;
	running_process->state = RUNNING;
	running_process->event_time = current_time;
	
	// record occurence of event
	print_event(*running_process);
	return false;
}



bool terminate_process(Queue *event_record, pcb_t *running_process, int current_time){
	running_process->state = TERMINATED;
	running_process->terminateTime = current_time;
	enqueue(event_record, *running_process);
	print_event(*running_process);
	return true;
}



void to_ready_queue(Heap *ready, Queue *event_occur){
	pcb_t arrive = dequeue(event_occur);
	insert_heap(ready, arrive);			// insert newly arrived process into ready queue.
	print_event(arrive);
}



bool preempt_process(Heap *ready, pcb_t *running_process, int current_time){
	// insert running process back to priority queue if its not completely terminated.
	insert_heap(ready, *running_process);
	running_process->state = READY;
	running_process->event_time = current_time;
	
	return true;
}


