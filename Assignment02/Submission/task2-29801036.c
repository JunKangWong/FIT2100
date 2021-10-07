/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

task 2 of shortest process remaining next scheduling implementation.
This implementation has the exact same priority function as the shortest process next
however, it is run ontop of the preemptive main function instead on non_preemptive
main function.

*/

#include "scheduling_algorithm.c"


int main(int argc, char** argv){
	char *source_path = NULL;
	store_path(&source_path, argv[1], argc == 1);
	
	// run shorter process next in preemptive mode so it will be shortest remaining time next.
	scheduling_algorithm(source_path, "results-2.txt", SHORTEST_PROCESS_NEXT, PREEMPTIVE);
	free(source_path);
	return 0;
}

