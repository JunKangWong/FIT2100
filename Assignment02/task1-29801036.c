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
/*Special enumerated data type for process state*/

int load_textfile_to_pcb_t_queue(char* filepath, Queue *pcb_t_q);
//oid first_come_first_serve(Queue *ready, Queue *pcb_t_q);
void first_come_first_serve(Queue *ready, Queue *pcb_t_q, pcb_t *fcfs_memo);

int main(){
	Queue q1, q2;
	pcb_t *memo;
	int i;
	initialise_queue(&q1);
	initialise_queue(&q2);
	
	load_textfile_to_pcb_t_queue("processes.txt", &q1);
	int count = q1.item_count;
	

	
	first_come_first_serve(&q2, &q1, memo);

	
	/*
	for (i=0; i < count; i++){
		pcb_t current_process = dequeue(&q1);
		printf("process_name: %s. arrival_time: %d. service_time: %d\n",
		 current_process.process_name,
		 current_process.entryTime,
		 current_process.serviceTime);
	}
	*/
	
	return 0;
}


/*This function loads data in the text file (in arriving order) into a pcb_t queue.*/
int load_textfile_to_pcb_t_queue(char* filepath, Queue *pcb_t_q){
	FILE *fp;
	char *line = NULL;
	const char* delimiter = " ";
	size_t len = 0;
	ssize_t read;
	int count;

	fp = fopen(filepath, "r");
	
	if(fp == NULL) {
		printf("invalid file path");
		return 0;
	}

	while ((read = getline(&line, &len, fp)) != -1){
	
		////// break this part into function///////
		pcb_t process;
		count = 1;
		
		// retrieve first token
		char *token = strtok(line, delimiter);
		strcpy(process.process_name, token);
		process.state = READY; // set default state as READY.
		
		//printf("%s", token);
		while(token != NULL){
			token = strtok(NULL, " ");
			
			switch(count)
			{
				case 1: {
					process.entryTime = atoi(token);
					//printf("case1: %d\n", atoi(token));
					break;
				}case 2: {
					process.serviceTime = atoi(token);
					process.remainingTime = atoi(token);
					break;
				}case 3: {
					// do nothing for now
				}
			}
			count ++;
		}
		////// break this part into function///////
		enqueue(pcb_t_q, process);
	}
	fclose(fp);
	free(line);
}



void first_come_first_serve(Queue *ready, Queue *pcb_t_q, pcb_t *fcfs_memo){
	int current_time = 0, service_counter;
	bool completed = true;
	int active_process = 0;
	int count = 0;
	pcb_t running_process;
	pcb_t arrive;
	
	// make ready queue local?
	
	
	// may have some problem such that item count is finished by last item cannot run.
	
	// run while there are still process to be run or any remaining process is still running.
	// || remaining_process > 0)
	while(pcb_t_q->item_count > 0 || active_process > 0){
		
		// enqueue entry/ arrival process (while loop incase multiple same arrival time)
		while(pcb_t_q->value[(pcb_t_q->front) + 1].entryTime == current_time){
			//printf("time: %d, entry_time: %d, process_name: %s\n",current_time, pcb_t_q->value[(pcb_t_q->front)+1].entryTime, pcb_t_q->value[(pcb_t_q->front)+1].process_name);

			arrive = dequeue(pcb_t_q);
			enqueue(ready, arrive);
			active_process ++;
			
			
			printf("Time: %d. ARRIVE: process_name: %s. arrival_time: %d. service_time: %d\n",
			 current_time,
			 arrive.process_name,
			 arrive.entryTime,
			 arrive.serviceTime);
			
			//fcfs_memo[count] = arrive;
			//count ++;
		}
		
		//printf("time: %d, item_count b4: %d\n",current_time,ready->item_count);

		
		// if there is process ready for execution and previous process has completed execution
		if(ready->item_count > 0 && completed){

			running_process = dequeue(ready);
			running_process.state = RUNNING;
			completed = false;
			
			printf("Time: %d. RUNING: process_name: %s. arrival_time: %d. service_time: %d\n",
			 current_time,
			 running_process.process_name,
			 running_process.entryTime,
			 running_process.serviceTime);
			
			// store for output
			//fcfs_memo[count] = running_process;
			//count ++;
		}
		
		// when there are incompleted process to be completed.
		if(!completed){
			//run the process and deduct 1 from the remainingTime
			
			
			// if process completed running
			if(running_process.remainingTime == 0){
				running_process.state = EXIT;
				completed = true; // indicate new process can be schduled to run.
				active_process --;
				
				printf("TIme: %d. EXIT: process_name: %s. arrival_time: %d. service_time: %d\n",
				 current_time,
				 running_process.process_name,
				 running_process.entryTime,
				 running_process.serviceTime);
				
				/// store for output
				//fcfs_memo[count] = running_process;
				//count ++;
			}
			running_process.remainingTime = running_process.remainingTime-1;
		}
		

		// + 1 second
		current_time ++;
	}
}







/*

int load_textfile_to_pcb_t_queue(char* filepath, Queue pcb_t_q){
	FILE *fp;
	char *line = NULL;
	const char* delimiter = " ";
	size_t len = 0;
	ssize_t read;
	int count;

	fp = fopen(filepath, "r");
	
	if(fp == NULL) {
		printf("invalid file path");
		return 0;
	}

	while ((read = getline(&line, &len, fp)) != -1){
	
		////// break this part into function///////
		pcb_t process;
		count = 1;
		
		// retrieve first token
		char *token = strtok(line, delimiter);
		strcpy(process.process_name, token);
		process.state = READY;
		
		//printf("%s", token);
		while(token != NULL){
			token = strtok(NULL, " ");
			
			switch(count)
			{
				case 1: {
					process.entryTime = atoi(token);
					//printf("case1: %d\n", atoi(token));
					break;
				}case 2: {
					process.serviceTime = atoi(token);
					process.remainingTime = atoi(token);
					//printf("case2: %d\n", atoi(token));
					
					break;
				}case 3: {
					// do nothing for now
				}
			}
			count ++;
		}
		////// break this part into function///////

		
		enqueue(&pcb_t_q, process);
	}
	fclose(fp);
	free(line);
}
*/



/*
int first_come_first_serve(char* filepath){
	FILE *fp;
	char *line = NULL;
	const char* delimiter = " ";
	size_t len = 0;
	ssize_t read;

	fp = fopen(filepath, "r");
	
	if(fp == NULL) {
		printf("yes");
		return 0;
	}
	
	
	while ((read = getline(&line, &len, fp)) != -1){
		//printf("%ld", read);
		//printf("%s", line);
		
		// retrieve first token
		char *token = strtok(line, delimiter);
		
		while(token != NULL){
			printf("%s", token);
			token = strtok(NULL, delimiter);
		}
		
	}
	
	fclose(fp);
	free(line);
}
*/


//int load_text_into_queue









