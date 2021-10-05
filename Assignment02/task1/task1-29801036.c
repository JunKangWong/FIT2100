#include "task1-29801036.h"

/*
Input filename: processes.txt
Output filename: result-tasknum.txt

Format of processes.txt
<process_name> <entryTime> <serviceTime> <deadline>

Sorted in order of arrival time
MUST NOT assume there will not be no processes with the same arrival time
i.e. processes can have the same arrival time.

e.g.
P1 0 3 5
P2 1 6 7
P3 4 4 6
P4 6 2 2
.
.
.P100 (Maximum)
*/

int main(){
	Queue event_occur, event_record;
	initialise_queue(&event_occur);
	initialise_queue(&event_record);

	// load textfile "processes.txt" into event_occur queue for processing.
	load_textfile_to_pcb_t_queue("processes.txt", &event_occur);
	
	// simulates first come first serve process scheduler and record event into event_record queue.
	first_come_first_serve(&event_occur, &event_record);
	
	// generate an output file according to the recorded events in event_record queue.
	generate_output_file("results-1.txt", &event_record);
}


/*
Given a event queue this function simulates event based on the event queue by a time tick
of 1 second per cycle. This function simulates the first come first serve scheduler 
behaviour and produce a sequence of pcb_t struct object in order of event occurence into
the struct queue as a record.

Argument: 

Queue *event_occur,: queue containing the "future" event that will occur.
Queue *event_record: queue that records the event occur.
*/
void first_come_first_serve(Queue *event_occur, Queue *event_record){

	int current_time = 0, active_process = 0;
	bool completed = true;
	pcb_t running_process;
	
	Queue ready;
	initialise_queue(&ready);

	// run while there are still process to be run or any remaining process is still running.
	// this outer while loop simulates clock ticks
	while(event_occur->item_count > 0 || active_process > 0){

		// enqueue entry/ arrival process (while loop incase multiple same arrival time)
		while(event_occur->value[(event_occur->front) + 1].entryTime == current_time){
			to_ready_queue(&ready, event_occur);
			active_process ++;
		}

		// when there are incompleted process to be completed.
		if(!completed){
			//run the process and deduct 1 from the remainingTime
			running_process.remainingTime --;
			// if process completed running
			if(running_process.remainingTime == 0){
				completed = terminate_process(event_record,&running_process, current_time);
				active_process --;
			}
		}
		// if there is process ready for execution and previous process has completed execution
		if(ready.item_count > 0 && completed){
			completed = schedule_process(&ready, &running_process, current_time);
		}
		// + 1 second (clock tick by 1 second)
		current_time ++;
	}
}



bool schedule_process(Queue* ready, pcb_t *running_process, int current_time){
	*running_process = dequeue(ready);
	running_process->state = RUNNING;
	running_process->event_time = current_time;
	// upddate first served time only if remaining equals service time (first serve)
	running_process->firstServedTime  = (running_process->remainingTime == running_process->serviceTime) ? 
	current_time : running_process->firstServedTime;
	running_process->event_time = current_time;
	
	// print event to terminal
	print_event(*running_process);
	return false;
}


bool terminate_process(Queue* event_record, pcb_t *running_process, int current_time){
	running_process->state = TERMINATED;
	running_process->terminateTime = current_time;
	enqueue(event_record, *running_process);
	
	/// print the event to standard out.
	print_event(*running_process);
	return true;
}


void to_ready_queue(Queue *ready, Queue *event_occur){
	pcb_t arrive = dequeue(event_occur);
	enqueue(ready, arrive);
	// print event at standard out.
	print_event(arrive);
}



