#include "scheduling_algorithm.c"


int main(int argc, char** argv){
	char *source_path = NULL;
	store_path(&source_path, argv[1], argc == 1);
	scheduling_algorithm(source_path, "results-1.txt", FIRST_COME_FIRST_SERVE, NON_PREEMPTIVE);
	return 0;
}
