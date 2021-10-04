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
			case TERMINATED:
				fprintf(fp, "Time %d: %s has finished execution.\n", cur_event.current_time, cur_event.process_name);
				break;
			case EXIT:
				fprintf(fp, "Time %d: %s has been preempted.\n", cur_event.current_time, cur_event.process_name);
				break;
		}
	}
	fclose(fp);
}

