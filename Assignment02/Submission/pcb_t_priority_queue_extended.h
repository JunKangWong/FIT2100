/*
Name            : Wong Jun Kang
StudentID       : 29801036
Date created    : 01/10/2021
Last Modified   : 07/10/2021

The header file of pcb_t_priority_queue_extended.c
*/
#ifndef PQ_H
#define PQ_H
#include <stdbool.h>
#include "process_structure.h"



typedef enum {
	SHORTEST_PROCESS_NEXT, MAXIMISE_DEADLINE, FIRST_COME_FIRST_SERVE
}priority;


typedef struct{
	pcb_t *arr;
	int size, capacity, lifetime_counter; // current size and maximum capacity;
	priority priority_rule; 
}Heap;


/*Function Prototype*/
Heap* init_heap(int capacity, priority operation_mode);
int parent(int i);
int left_child(int i);
int right_child(int i);
pcb_t get_root(Heap* heap);
void swap(Heap* heap, int x, int y);
bool is_higher_priority(Heap* heap, pcb_t x, pcb_t y);
bool first_come_first_serve(pcb_t x, pcb_t y);
bool shorter_remaining_time_first(pcb_t x, pcb_t y);
bool maximise_processes(Heap* heap, pcb_t x, pcb_t y);
bool deadline_test(pcb_t p, int current_time);
Heap* insert_heap(Heap* heap, pcb_t elem);
Heap* heapify(Heap* heap, int index);
Heap* delete_root(Heap* heap);
pcb_t extract_root(Heap* heap);
void print_heap(Heap* heap);
void free_heap(Heap* heap);


#endif /* PQ_H */
