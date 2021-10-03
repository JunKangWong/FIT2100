#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.c"

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


/*Function Prototype*/
int load_textfile_to_pcb_t_queue(const char* filepath, Queue *pcb_t_q);
void first_come_first_serve(Queue *pcb_t_q, Queue *fcfs); // this one allow task 3 end and task 2 run immediately.
void generate_output_file(const char* filepath, Queue *res_queue);



int main(){
	int i;
	pcb_t cur_process;
	Queue event_occur, event_record;
	initialise_queue(&event_occur);
	initialise_queue(&event_record);

	// load textfile "processes.txt" into event_occur queue for processing.
	load_textfile_to_pcb_t_queue("processes.txt", &event_occur);
	
	// simulates first come first serve process scheduler and record event into event_record queue.
	first_come_first_serve(&event_occur, &event_record);
	
	// generate an output file according to the recorded events in event_record queue.
	generate_output_file("output.txt", &event_record);
}




/*
This function opens text file in the specified filepath and loads data in the 
text file (in  sequence of arriving order) into a pcb_t queue.

Argument: 

const char* filepath: filepath of the text file to be loaded pcb_t_q queue.
Queue *pcb_t_q: Buffer of Queue of structs for the text file to be loaded into.

Return: 0 when file is unsucessfully loaded, else return 1 indicate success.
*/
int load_textfile_to_pcb_t_queue(const char* filepath, Queue *pcb_t_q){
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pcb_t proc;


	fp = fopen(filepath, "r");
	
	if(fp == NULL) {
		printf("invalid file path");
		return 0;
	}
	
	while(fscanf(fp, "%s %d %d %d\n", proc.process_name, &(proc.entryTime), &(proc.serviceTime), &(proc.deadline)) > 0){
		proc.remainingTime = proc.serviceTime;
		proc.state = READY;
		enqueue(pcb_t_q, proc);
	}
	
	fclose(fp);
	free(line);
	return 1;
}



/*
Given a event queue this function simulates event based on the event queue by a time tick
of 1 second per cycle. This function simulates the first come first serve scheduler 
behaviour and produce a sequence of pcb_t struct object in order of event occurence into
the struct queue as a record.

Argument: 

Queue *pcb_t_q,: queue containing the "future" event that will occur.
Queue *fcfs: queue that records the event occur.
*/
void first_come_first_serve(Queue *pcb_t_q, Queue *fcfs){

	int current_time = 0, service_counter;
	bool completed = true;
	int active_process = 0;
	pcb_t running_process;
	pcb_t arrive;
	
	Queue ready;
	initialise_queue(&ready);

	// run while there are still process to be run or any remaining process is still running.
	// this outer while loop simulates clock ticks
	while(pcb_t_q->item_count > 0 || active_process > 0){

		// enqueue entry/ arrival process (while loop incase multiple same arrival time)
		while(pcb_t_q->value[(pcb_t_q->front) + 1].entryTime == current_time){
			
			// retrieved process from "non_visible queue" and place it into the ready queue.
			arrive = dequeue(pcb_t_q);
			arrive.current_time = current_time;
			enqueue(&ready, arrive);
			active_process ++;
			
			// record arrival event in an array for output purposes.
			enqueue(fcfs, arrive); 
		}

		// when there are incompleted process to be completed.
		if(!completed){
			//run the process and deduct 1 from the remainingTime
			running_process.remainingTime = running_process.remainingTime-1;
			// if process completed running
			if(running_process.remainingTime == 0){
				running_process.state = EXIT;
				running_process.current_time = current_time;
				completed = true; // indicate new process can be schduled to run.
				active_process --;

				/// store event at output buffer.
				enqueue(fcfs, running_process);
			}
		}
		// if there is process ready for execution and previous process has completed execution
		if(ready.item_count > 0 && completed){

			running_process = dequeue(&ready);
			running_process.state = RUNNING;
			running_process.current_time = current_time;
			completed = false;

			// store  event
			enqueue(fcfs, running_process);
		}
		
		// + 1 second (clock tick by 1 second)
		current_time ++;
	}
}


/*
Given the event_record queue. This function formats and writes the data in the queue
into a file as specified in the filepath.

Argument: 
const char* filepath: filepath to write the text file to.
Queue *res_queue: queue containing process information to be written into the textfile.
*/
void generate_output_file(const char* filepath, Queue *res_queue){
	FILE *fp;
	fp = fopen(filepath, "w");
	pcb_t cur_event;
	
	while(res_queue->item_count > 0){
		cur_event = dequeue(res_queue);
		
		switch(cur_event.state){
			case READY:
				fprintf(fp, "Time %d: %s has entered the system.\n", cur_event.current_time, cur_event.process_name);
				break;
			case RUNNING:
				fprintf(fp, "Time %d: %s is in the running state.\n", cur_event.current_time, cur_event.process_name);
				break;
			case EXIT:
				fprintf(fp, "TIme %d: %s has finished the running state.\n", cur_event.current_time, cur_event.process_name);
				break;
		}
	}
	fclose(fp);
}









