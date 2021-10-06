//#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "process_structure.h"

typedef enum {
	SHORTEST_REMAINING_TIME, MAXIMISE_DEADLINE, FIRST_COME_FIRST_SERVE
}priority;


typedef struct{
	pcb_t *arr;
	int size, capacity, lifetime_counter; // current size and maximum capacity;
	priority priority_rule; 
}Heap;


/*Function Prototype*/
int parent(int i);
int left_child(int i);
int right_child(int i);
pcb_t get_min(Heap* heap);
Heap* init_heap(int capacity, priority operation_mode);
Heap* insert_heap(Heap* heap, pcb_t elem);
void swap(Heap* heap, int x, int y);
bool is_higher_priority(Heap* heap, pcb_t x, pcb_t y);
bool first_come_first_serve(pcb_t x, pcb_t y);
bool shorter_remaining_time_first(pcb_t x, pcb_t y);
bool deadline_test(pcb_t p, int current_time);
bool maximise_processes(Heap* heap, pcb_t x, pcb_t y);
void free_heap(Heap* heap);
void print_heap(Heap* heap);
Heap* heapify(Heap* heap, int index);
Heap* delete_minimum(Heap* heap);
pcb_t extract_min(Heap* heap);
