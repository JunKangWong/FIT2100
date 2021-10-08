/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

Referenced and modified from:
https://gist.github.com/kuriringohankamehameha/e793d66152ce95cecf0d05db04ec1ce8 

This module supports a priority queue functionality.
A priority function is created to decide the priority of the scheduling algorithms.
*/

/*header file*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process_structure.h"
#include "pcb_t_priority_queue_extended.h"

/*
Function to initialise priority queue.

Argument:
int capacity: capacity of the priority queue.
priority opermation_mode: priority function selector.

return: heap, the initialised priority queue.

*/
Heap* init_heap(int capacity, priority operation_mode){
	Heap* heap = (Heap*) calloc (1, sizeof(Heap));
	heap->arr = (pcb_t*) calloc (capacity, sizeof(pcb_t));
	heap->capacity = capacity;
	heap->size = 0;
	heap->priority_rule = operation_mode;
	return heap;
}


/*
This function takes in an index and return its parent index.

Argument:
int i: current index

return: parent index of current index
*/
int parent(int i){
	return (i-1)/2;
}


/*
This function takes in an index and return its left_child index

Argument:
int i: current index

return: index of left child.
*/
int left_child(int i){
	return (2*i + 1);
}


/*
This function takes in an index and return its right_child index.

Argument:
int i: current index

return: index of right_child.
*/
int right_child(int i){
	return (2*i + 2);
}


/*
This function get the root of the priority queue (heap).

Argument:
Heap* heap: the heap to retrive root from

return: the root node of the heap.
*/
pcb_t get_root(Heap* heap){
	return heap -> arr[0];
}


/*
This function swaps node x with node y  in a heap.

Argument:
Heap* heap: the heap to perform swapping on
int x: index of the node to be swapped with node at index y.
int y: index of the node to be swapped with ndoe at index x.
*/
void swap(Heap* heap, int x, int y){
	pcb_t temp = heap->arr[x];
	heap->arr[x] = heap->arr[y];
	heap->arr[y] = temp;
}


/*
The priority function that decides the ordering of the priority queue.
This function will picks the priority function based on the priority_rule specified 
during heap initialisation (init_heap).

Argument:
Heap *heap: heap to compare priority on
pcb_t x: the pcb_t object to be compared with y.
pcb_t y: the pcb_t object to be compared with x.

return: is_x_higher_priority, bool true/ false, true indicate higher priority.
false otherwise.

*/
bool is_higher_priority(Heap* heap, pcb_t x, pcb_t y){
	bool is_x_higher_priority;
	
	switch(heap->priority_rule){
		case FIRST_COME_FIRST_SERVE:
			is_x_higher_priority = first_come_first_serve(x, y);
			break;
		case SHORTEST_PROCESS_NEXT:
			is_x_higher_priority = shorter_remaining_time_first(x, y);
			break;
		case MAXIMISE_DEADLINE:
			is_x_higher_priority = maximise_processes(heap, x, y);
			break;
	}
	return is_x_higher_priority;
}



/*
This function describes the priority of a first come first serve scheduller.

if x.entryTime is smaller than y.entryTime, return true indicating that x has 
a higher priority, if y.entryTime is smalelr than x.entryTime return false,
indicate that x has a lower priority. If both x and y has equal entryTime, 
return the process with smaller serviceTime. If both process has equal serviceTime
the process x will be given a higher priority.

Argument:
pcb_t x: the pcb_t object to be compared with y.
pcb_t y: the pcb_t object to be compared with x.

return: bool true/ false, true indicate higher priority.
false otherwise.

*/
bool first_come_first_serve(pcb_t x, pcb_t y){
	if (x.entryTime < y.entryTime){
		return true;
	}else if (y.entryTime < x.entryTime){
		return false;
	}else{
		if(x.serviceTime <= y.serviceTime){
			return true;
		}else{
			return false;
		}
	}
}



/* 
This function compares the priority of process x and y.
if process x is has a smaller remaining time return true else false.
if process x and y has equal remainingTime, compare entryTime.
if process x is has a smaller entryTime return true else false.
if both process has the same entryTime return true, indicate process x has a greater priority.

Argument:
pcb_t x: the pcb_t object to be compared with y.
pcb_t y: the pcb_t object to be compared with x.

return: bool true/ false, true indicate higher priority.
false otherwise.

*/
bool shorter_remaining_time_first(pcb_t x, pcb_t y){
	if (x.remainingTime < y.remainingTime){
		return true;
		
	}else if (y.remainingTime < x.remainingTime){
		return false;
		
	}else{ // x.remainingTime equals y.remainingTime
	
		if (x.entryTime <= y.entryTime){
			return true;
		}else{
			return false;
		}
	}
}


/*
This function maximises the number of processes to be completed before the deadline is met.
This function has its logic construct assuming a non preemptive context.

Argument:
Heap* heap: heap which the comparison is compared based on.
pcb_t x: the pcb_t object to be compared with y.
pcb_t y: the pcb_t object to be compared with x.

return: bool true/ false, true indicate higher priority.
false otherwise.
*/
bool maximise_processes(Heap* heap, pcb_t x, pcb_t y){
	int current_time = heap->lifetime_counter;
	int X = x.entryTime + x.deadline; 
	int Y = y.entryTime + y.deadline;
	bool X_pass = deadline_test(x, current_time);
	bool Y_pass = deadline_test(y, current_time);
	
	// if both process x and process y passes the deadline test
	// meaning that they both can meet deadline if scheduled now.
	if (X_pass && Y_pass){
		// return the process with sooner deadline 
		if(X <= Y){
			return true;
		}else{
			return false;
		}
	// x has higher priority if, x can meet deadline
	}else if(X_pass && !Y_pass) {
		return true;
	// x has lower priority if, x cannot meet deadline
	}else if(!X_pass && Y_pass){
		return false;
	// process with shorter remainingTime has higher priority if both processes cannot meet deadline.
	}else{
		return shorter_remaining_time_first(x, y);
	}
}


/*
This function checks whether deadline can be met if the process is scheduled at
current_time.

Argument:
pcb_t p: the process to check the condition on
int current_time: current time of the scheduling cycle.

return: boolean true if process can meet deadline, false otherwise.
*/
bool deadline_test(pcb_t p, int current_time){
	return current_time + p.remainingTime <= p.entryTime + p.deadline;
}


/*
This function inserts a pcb_t element into the pcb_t priority queue.
If the capacity of the heap is full, return the heap without inserting the element.

Argument:
Heal *heap: heap to be inserted into
pcb_t elem: element to be inserted.

return: Heap* heap, with the inserted element.

*/
Heap* insert_heap(Heap* heap, pcb_t elem){

	if(heap->size == heap->capacity){
		fprintf(stderr, "maximum capacity reached for the heap!");
		return heap;
	}
	
	// increment size first
	// then, insert element as the last element of the heap.
	heap->size++; 
	heap->arr[heap->size -1] = elem;
	
	// keep swapping the element upwards until it reaches the root.
	int curr = heap->size - 1;
	
	// while not root and child has a higher priority than children
	while(curr > 0 && is_higher_priority(heap, heap->arr[curr],heap->arr[parent(curr)])){
		swap(heap, parent(curr), curr); // swap parent and child in the heap.
		curr = parent(curr);
	}
	return heap;
}



/*
Performing heapify recursively.
Rearranging the heap as to maintain the heap property.

Argument:
Heap* heap: heap to perform heapify on
int index: index to start the heapify process from.

return: properly ordered heap.
*/
Heap* heapify(Heap* heap, int index){
	
	// if there is only 1 element left in the heap which is the root
	// do nothing and return the root itself.
	if (heap->size<= 1){
		return heap;
	}
	
	int left = left_child(index);
	int right = right_child(index);
	
	int highest_priority = index;
	
	// if left is not the last element/ leaf
	// if left child of element at index has a higher priority than element at index
	if(left < heap->size && is_higher_priority(heap, heap->arr[left], heap->arr[index])){
		highest_priority = left;
	}
	
		// if left is not the last element/ leaf
	// if left child of element at index has a higher priority than element at index
	if(right < heap->size && is_higher_priority(heap, heap->arr[right], heap->arr[highest_priority])){
		highest_priority = right;
	}
	
	if(highest_priority != index){
		swap(heap, index, highest_priority);
		heap = heapify(heap, highest_priority);
	}
	return heap;
}



/*
Given heap, this function deletes the root node of the heap and perform heapify 
to maintain the heap property.

Argument:
Heap* heap: heap to have its root deleted from

return: Heap* heap object with its original root deleted.

*/
Heap* delete_root(Heap* heap){
	// if heap is empty, dont delete and return back the empty heap.
	if(!heap || heap->size == 0){
		return heap;
	}

	int size = heap->size;
	pcb_t last_elem = heap->arr[size-1];
	
	// replace the last element in the heap as the root.
	heap->arr[0] = last_elem;
	
	heap->size--;

	return heapify(heap, 0);
}

/*
This function extract the root node from the priority queue.
This function first get the root node of the heap then run delete_root to delete 
the root node from the heap.

Argument:
Heap* heap: heap to have its root node extracted.

return: pcb_t root process extracted from the heap.
*/
pcb_t extract_root(Heap* heap){

	// get root item then delete the item.
	pcb_t process = get_root(heap);
	delete_root(heap);
	return process;

}

/*

This function formats the heap and print the process_name of the of the pcb_t object 
stored in the heap.

Argument:
Heap* heap: heap to be printed.
*/
void print_heap(Heap* heap){

	printf("pcb_t Heap:\n");
	
	for(int i=0; i < heap->size; i++){
		printf("%s -> ", heap->arr[i].process_name);
	}
	printf("\n");
}

/*
This function free up the memory allocated to the heap object.

Argument:
Heap* heap: heap to be freed.
*/
void free_heap(Heap* heap){
	if (!heap)
		return;	
	free(heap->arr);
	free(heap);
}
