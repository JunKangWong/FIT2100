/*
Name            : Wong Jun Kang
StudentID       : 29801036
Date created    : 01/10/2021
Last Modified   : 07/10/2021

This module contains functions that changes the state of the process.
These function not only update the state but also other relevant information like
time of termination, remainingTime etc.

*/
#include <stdbool.h>
#include "change_process_state.h"
#include "process_structure.h"
#include "pcb_t_file_io.h"
#include "pcb_t_queue.h"
#include "pcb_t_priority_queue_extended.h"


/*
This function change the process state from READY to RUNNING.
this function will extract new process with the highest priority to run.
while calculates necessary information for final calculations.

*ready: the ready queue of the scheduler,extratced root will be inserted into this ready queue..
pcb_t * running_process: the current running_process buffer to be updated.
int current_time: current time to be recorded when preemption (reschedule) or first served time 
is needed to be updated.

return: bool false, indicate that a process has entered and completed process is false.
*/
bool schedule_process(Heap *ready, pcb_t *running_process, int current_time){
	// update firstServedTime only when remainingTime equals to firstServedTime.
	*running_process = extract_root(ready);
	
	// update first served time if its remaining time equals the  serviceTime, implying
	// its first time running, update firstServedTime.
	running_process->firstServedTime = (running_process->remainingTime == running_process->serviceTime) ?
	current_time : running_process->firstServedTime;
	running_process->state = RUNNING;
	// record event time in case of reschefuled again due to  preemption if this information is ever needed.
	running_process->event_time = current_time; 
	
	// record occurence of event
	print_event(*running_process);
	return false;
}



/*
This function will change the process state from RUNNING to TERMINATED.
terminatedTime will be updated in this function.
the results will be enqueue in this function (fcfs). Meaning that, the final output
will be sorted by order of termination

*event_record: a queue that records the event that occur, which is to be outputed
into the result file in the end.
pcb_t * running_process: the current running_process buffer to be updated.
int current_time: current_time of the scheduler. To update the terminated time during
process termination.

return: boolean true indicate that the current process has been completed and new process
can be scheduled if there is any.

*/
bool terminate_process(Queue *event_record, pcb_t *running_process, int current_time){
	running_process->state = TERMINATED;
	running_process->terminateTime = current_time;
	enqueue(event_record, *running_process);
	print_event(*running_process);
	return true;
}


/*
This function doesnt change state as process is READY by default.
This function will enqueue/ insert newly arrived process into the ready queue.


*ready: the ready queue of the scheduler,newly arrievd will be inserted into this ready queue..
Queue *event_occur: queue containing "future" events to be inserted into the ready queue.
*/
void to_ready_queue(Heap *ready, Queue *event_occur){
	pcb_t arrive = dequeue(event_occur);
	insert_heap(ready, arrive);			// insert newly arrived process into ready queue.
	print_event(arrive);
}



/*
This function is called when a process is to be preempted back into the ready queue.
meaning that, the remainingTime is still not 0 (not yet terminated) AND
the time quantum has been reached for the current process AND there exists another
process that has a higher priority than the current running process.

Heap* ready: ready queue of the scheduler.
pcb_t *running_process: process that is currently running, which is about to be preempted back into queue.
int current_time: current time when the preemption happened.

return: boolean true, indicate that current process is preempted back into the queue.
*/
bool preempt_process(Heap *ready, pcb_t *running_process, int current_time){
	// insert running process back to priority queue if its not completely terminated.
	insert_heap(ready, *running_process);
	running_process->state = READY;
	running_process->event_time = current_time;
	
	return true;
}
