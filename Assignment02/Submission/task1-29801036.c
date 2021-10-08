/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

First come first serve is chosen as the default method for task 1.
Though changing the 3rd parameter into "SHORTEST_PROCESS_NEXT", will be
switched to shorest process next implementation.

*/
#include <stdlib.h>
#include "scheduling_algorithm.h"
#include "pcb_t_file_io.h"
#include "pcb_t_priority_queue_extended.h"


int main(int argc, char** argv){
	char *source_path = NULL;
	store_path(&source_path, argv[1], argc == 1);
	
	// run first_come_first serve in a non_preemptive context.
	execute_non_preemptive(source_path, "results-1.txt", FIRST_COME_FIRST_SERVE);
	free(source_path);
	return 0;
}


