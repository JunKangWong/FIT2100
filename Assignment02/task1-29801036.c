#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int main(){
	Queue q1, q2;
	int i;
	initialise_queue(&q1);
	initialise_queue(&q2);
	
	
	
	
	load_textfile_to_pcb_t_queue("processes.txt", &q1);
	int count = q1.item_count;
	
	printf("count: %d\n",count);
	
	for (i=0; i < count; i++){
		pcb_t current_process = dequeue(&q1);
		printf("process_name: %s. arrival_time: %d. service_time: %d\n",
		 current_process.process_name,
		 current_process.entryTime,
		 current_process.serviceTime);
	}
	
	return 0;
}


/*This function loads data in the text file into a pcb_t queue.*/
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
		enqueue(pcb_t_q, process);
	}
	fclose(fp);
	free(line);
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









