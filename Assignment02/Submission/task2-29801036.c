#include "scheduling_algorithm.c"


int main(int argc, char** argv){
	char *source_path = NULL;
	store_path(&source_path, argv[1], argc == 1);
	scheduling_algorithm(source_path, "results-2.txt", SHORTEST_REMAINING_TIME, PREEMPTIVE);
	return 0;
}
