/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

This module contains the main logic used for the scheduling algorithm.
*/
#include "scheduling_algorithm.h"


/*
This function is used to run and execute the scheduling algorithm.
A selector enum parameter needs to be specified for the user to select their desired 
schedule_mode.

const char* source_path: path containing the source file to be processed.
const char* dest_path: destination path to save the processed files.
priority priority_rule: the priority rule selector. Specified the enum, to select 
priority_rule between:
FIRST_COME_FIRST_SERVE: based on first come first serve priority function 
SHORTEST_REMAINING_NEXT: based on shortest remaining next priority function 
MAXIMISE_DEADLINE: maximise the number of processes to meet deadlines.

schedule_mode mode: selecttor of PREEMTIVE or NON_PREEMPTIVE operation mode.
*/
void scheduling_algorithm(const char* source_path, const char* dest_path, priority priority_rule, schedule_mode mode){
	Queue event_occur, event_record;
	initialise_queue(&event_occur);
	initialise_queue(&event_record);

	// load textfile "processes.txt" into event_occur queue for processing.
	load_textfile_to_pcb_t_queue(source_path, &event_occur);
	
	// select operation mode based on the mode selector.
	switch (mode){
		case PREEMPTIVE:
			preemptive_scheduling(&event_occur, &event_record, priority_rule);
			break;
		case NON_PREEMPTIVE:
			non_preemptive_scheduling(&event_occur, &event_record, priority_rule);
			break;
	}
	// generate an output file according to the recorded events in event_record queue.
	generate_output_file(dest_path, &event_record);
}



/*
This function simulates the execution of a preemptive scheduling operation.

Queue *event_occur: containing a list of "future" events to be loaded into the ready queue.
Queue *event_record: Status of the terminated process. This is stored to be output in log file later.

priority priority_rule: the priority rule selector. Specified the enum, to select 
priority_rule between:
FIRST_COME_FIRST_SERVE: based on first come first serve priority function 
SHORTEST_REMAINING_NEXT: based on shortest remaining next priority function 
MAXIMISE_DEADLINE: maximise the number of processes to meet deadlines.

*/
void preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule){
	int time_quant = 0, current_time = 0, active_process = 0;
	bool completed = true;
	pcb_t running_process;
	
	// initialise a priority queue (min heap) based on priority rule
	Heap* ready = init_heap(SIZE, priority_rule);
	ready->lifetime_counter = 0; // stores the lifetime of the ready queue.
	
	// while there are still process to be loaded.
	// This outer loop simulates clock tick.
	while(event_occur->item_count > 0 || active_process > 0){
		
		// simulates arrival of process
		while(event_occur->value[(event_occur->front)+1].entryTime == current_time){
			to_ready_queue(ready, event_occur);
			active_process ++;
		}
		
		// simulate running of processes
		if (!completed){
			running_process.remainingTime --;
			time_quant --;
			
			if(running_process.remainingTime == 0){
				completed = terminate_process(event_record, &running_process, current_time);
				active_process --;

			}else if(time_quant == 0){
				// if running process is still the highest priority process after time quantum is over.
				// continue to run --> reset time quantum
				if(is_higher_priority(ready, running_process, get_root(ready))){
					time_quant = TIME_QUANTUM; 
				}else{
					completed = preempt_process(ready, &running_process, current_time); 
				}
			}
		}
		// simulates scheduling of process
		// if current process completes running andready queue has element to be scheduled.
		if(ready->size > 0 && completed){
			time_quant = TIME_QUANTUM; // reset time quantum
			completed = schedule_process(ready, &running_process, current_time);
		}
		// clock tick by 1 second
		ready->lifetime_counter = ++current_time;
	}
	// free up memory of ready queue.
	free_heap(ready);
}



/*
This function simulates the execution of a non preemptive scheduling operation.

Queue *event_occur: containing a list of "future" events to be loaded into the ready queue.
Queue *event_record: Status of the terminated process. This is stored to be output in log file later.

priority priority_rule: the priority rule selector. Specified the enum, to select 

priority_rule between:
FIRST_COME_FIRST_SERVE: based on first come first serve priority function 
SHORTEST_REMAINING_NEXT: based on shortest remaining next priority function 
MAXIMISE_DEADLINE: maximise the number of processes to meet deadlines.
*/
void non_preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule){
	int current_time = 0, active_process = 0;
	bool completed = true;
	pcb_t running_process;
	
	// initialise a priority queue (min heap) based on remainingTime.
	Heap* ready = init_heap(SIZE, priority_rule);
	ready->lifetime_counter = 0; // stores the lifetime of the ready queue.
	
	// while there are still process to be loaded.
	// This outer loop simulates clock tick.
	while(event_occur->item_count > 0 || active_process > 0){
		
		// simulates arrival of process
		while(event_occur->value[(event_occur->front)+1].entryTime == current_time){
			to_ready_queue(ready, event_occur);
			active_process ++;
		}
		
		// simulate running of processes
		if (!completed){
			running_process.remainingTime --;
			
			if(running_process.remainingTime == 0){
				completed = terminate_process(event_record, &running_process, current_time);
				active_process --;
			}
		}
		// simulates scheduling of process
		// if current process completes running andready queue has element to be scheduled.
		if(ready->size > 0 && completed){
			completed = schedule_process(ready, &running_process, current_time);
		}
		// clock tick by 1 second
		ready->lifetime_counter = ++current_time;
	}
	// free up memory of ready queue.
	free_heap(ready);
}
