/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

File io operations of pcb_t related items.
*/

#include "pcb_t_file_io.h"


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
	pcb_t proc;

	fp = fopen(filepath, "r");
	
	// checks if filepath exists.
	if(fp == NULL) {
		printf("invalid file path");
		return 0;
	}
	
	// load file into event occurence queue.
	while(fscanf(fp, "%s %d %d %d\n", proc.process_name, &(proc.entryTime), &(proc.serviceTime), &(proc.deadline)) > 0){
		proc.remainingTime = proc.serviceTime;
		proc.state = READY;
		enqueue(pcb_t_q, proc);
	}
	
	fclose(fp);
	return 1;
}


/*
a pcb_t object this function will print out relevant information accordingly.

Argument: 
pcb_t cur_event: process event to be printed.
*/
void print_event(pcb_t cur_event){
	switch(cur_event.state){
		case READY:
			printf("Time %d: %s has entered the system.\n", cur_event.entryTime, cur_event.process_name);
			break;
		case RUNNING:
			printf("Time %d: %s is in the running state.\n", cur_event.event_time, cur_event.process_name);
			break;
		case TERMINATED:
			printf("Time %d: %s has finished execution.\n", cur_event.terminateTime, cur_event.process_name);
			break;
	}
}


/*
Given a Queue, this function will calculates wait time, turnaround time and deadline_met.
then generate an output file in the following format:

<process_name> <wait time> <turnaround time> <deadline met>
 
const char* filepath: destination path to store the generated path.
Queue *res_queue: result queue which output file is generated on.
*/
void generate_output_file(const char* filepath, Queue *res_queue){
	FILE *fp;
	fp = fopen(filepath, "w");
	pcb_t cur_process;
	
	int turn_around_time = -1,  wait_time = -1, deadline_met = -1;
	
	while(res_queue->item_count > 0){
		cur_process = dequeue(res_queue);
		
		// calculate wait time, turnaround time and deadline met
		wait_time = cur_process.firstServedTime - cur_process.entryTime;
		turn_around_time = cur_process.terminateTime - cur_process.entryTime;
		deadline_met = (cur_process.deadline >= turn_around_time) ? 1 : 0;
		
		// writes calculated results into the file.
		fprintf(fp, "%s %d %d %d\n", cur_process.process_name, wait_time, turn_around_time, deadline_met);

	}
	fclose(fp);
}


/*
Given a path in string, this function store the string into the buffer.
if path is not provided, file will be set to the default "processes.txt"
file.

char **buffer: buffer in which the string path is stored.
const char* str: path in string to be stored into the buffer.
bool path_not_provided: boolean true of path is provided, false if it is not.

Return: boolean true if function run sucessfully without problem.

*/
bool store_path(char** buffer, const char* str, bool path_not_provided){
	if (path_not_provided){
		const char* default_filepath = "processes.txt"; 
		*buffer = (char*) malloc(strlen(default_filepath) + 1);
		strcpy(*buffer, "processes.txt");
		return true;
	}

	*buffer = (char*) malloc(strlen(str) + 1);

	if(*buffer == NULL){
		return false;
	}
	
	strcpy(*buffer, str);
	return true;
}
