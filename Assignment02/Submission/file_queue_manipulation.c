#include "file_queue_manipulation.h"


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
	return 1;
}


/*
Given the event_record queue. This function formats and writes the data in the queue
into a file as specified in the filepath.

Argument: 
const char* filepath: filepath to write the text file to.
Queue *res_queue: queue containing process information to be written into the textfile.
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



void generate_output_file(const char* filepath, Queue *res_queue){
	FILE *fp;
	fp = fopen(filepath, "w");
	pcb_t cur_process;
	
	int turn_around_time = -1,  wait_time = -1, deadline_met = -1;
	
	while(res_queue->item_count > 0){
		cur_process = dequeue(res_queue);
		
		wait_time = cur_process.firstServedTime - cur_process.entryTime;
		turn_around_time = cur_process.terminateTime - cur_process.entryTime;
		deadline_met = (cur_process.deadline >= turn_around_time) ? 1 : 0;

		fprintf(fp, "%s %d %d %d\n", cur_process.process_name, wait_time, turn_around_time, deadline_met);

	}
	fclose(fp);
}



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
