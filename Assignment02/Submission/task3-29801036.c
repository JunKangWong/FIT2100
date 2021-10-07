/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

task 3 of the implementation.
A non-preemptive implementation is chosen to achieve this.
A specially written priority function in the pcb_t_priority_queue_extended.c module is 
written to optimise the number of processes that meet deadlines.

*/

#include "scheduling_algorithm.c"


int main(int argc, char** argv){
	char *source_path = NULL;
	store_path(&source_path, argv[1], argc == 1);
	
	// this implementation maximizes the number of deadline met processes.
	scheduling_algorithm(source_path, "results-3.txt", MAXIMISE_DEADLINE, NON_PREEMPTIVE);
	//scheduling_algorithm(source_path, "results-3.txt", MAXIMISE_DEADLINE, PREEMPTIVE);
	free(source_path);
	return 0;
}
