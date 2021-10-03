#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task1-29801036.h"
#include "priority_queue.h"

#define SIZE 100
/*
1) write a malloc versin then convert to stack version later on to try out
1) test is_higher_priority
3) test swap
4) rename all variables
5) optimise some unnecessary parts
6) cite the orignal author of the code.

Referenced and modified from:

*/



Heap* init_heap(int capacity){
	Heap* heap = (Heap*) calloc (1, sizeof(Heap));
	heap->arr = (pcb_t*) calloc (capacity, sizeof(pcb_t));
	heap->capacity = capacity;
	heap->size = 0;
	return heap;
}


int parent(int i){
	return (i-1)/2;
}

int left_child(int i){
	return (2*i + 1);
}

int right_child(int i){
	return (2*i + 2);
}

pcb_t get_min(Heap* heap){
	return heap -> arr[0];
}

pcb_t extract_min(Heap* heap){

	// get min item then delete the item.
	pcb_t process = get_min(heap);
	delete_minimum(heap);
	return process;

}

/*Swap current with its parent*/
void swap(Heap* heap, int x, int y){
	pcb_t temp = heap->arr[x];
	heap->arr[x] = heap->arr[y];
	heap->arr[y] = temp;
}



Heap* insert_heap(Heap* heap, pcb_t elem){

	if(heap->size == heap->capacity){
		fprintf(stderr, "maximum capacity reached for min heap!");
		return heap;
	}
	
	// increment size first
	// then, insert element as the last element of the heap.
	heap->size++; 
	heap->arr[heap->size -1] = elem;
	
	// keep swapping the element upwards until it reaches the root.
	int curr = heap->size - 1;
	
	// while not root and child has a higher priority than children
	while(curr > 0 && is_higher_priority(heap->arr[curr],heap->arr[parent(curr)])){
		swap(heap, parent(curr), curr); // swap parent and child in the heap.
		curr = parent(curr);
	}
}



/*
Performing heapify recursively.
Rearranging the heap as to maintain the min-heap property.

*/
Heap* heapify(Heap* heap, int index){
	
	// if there is only 1 element left in the heap which is the root
	// do nothing and return the root itself.
	if (heap->size<= 1){
		return heap;
	}
	
	int left = left_child(index);
	int right = right_child(index);
	
	int smallest = index;
	
	// if left is not the last element/ leaf
	// if left child of element at index has a higher priority than element at index
	if(left < heap->size && is_higher_priority(heap->arr[left], heap->arr[index])){
		smallest = left;
	}
	
		// if left is not the last element/ leaf
	// if left child of element at index has a higher priority than element at index
	if(right < heap->size && is_higher_priority(heap->arr[right], heap->arr[smallest])){
		smallest = right;
	}
	
	if(smallest != index){
		swap(heap, index, smallest);
		heap = heapify(heap, smallest);
	}
	return heap;
}



Heap* delete_minimum(Heap* heap){
	// if heap is empty
	if(!heap || heap->size == 0){
		return heap;
	}

	int size = heap->size;
	pcb_t last_elem = heap->arr[size-1];
	
	// replace the last element in the heap as the root.
	heap->arr[0] = last_elem;
	
	heap->size--;
	size--; // why is this needed? // can try remove? !!!!
	
	// check if straight away return function call can or not.!!!!!!
	heap = heapify(heap, 0); // heapify from the root.
	return heap;
}


void print_heap(Heap* heap){

	printf("pcb_t Min Heap:\n");
	
	for(int i=0; i < heap->size; i++){
		printf("%s -> ", heap->arr[i].process_name);
	}
	printf("\n");
}


void free_heap(Heap* heap){
	if (!heap)
		return;	
	free(heap->arr);
	free(heap);
}





/* 
This function compares the priority of process x and y.
if process x is has a smaller remaining time return true else false.
if process x and y has equal remainingTime, compare entryTime.
if process x is has a smaller entryTime return true else false.
if both process has the same entryTime return true, indicate process x has a greater priority.


need to test this function.!!!!!!!!!!!!!!

*/
bool is_higher_priority(pcb_t x, pcb_t y){
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
May implement if require

MinHeap* delete_element(MinHeap* heap, int index){

}

void rise(){

}

*/

int main(){
	pcb_t proc1, proc2, proc3, proc4, proc5, proc6, proc7, proc8;
	
	// test is higher priority
	strcpy(proc1.process_name,"P1");
	proc1.remainingTime = 1;
	proc1.entryTime = 2;
	
	strcpy(proc2.process_name,"P2");
	proc2.remainingTime = 2;
	proc2.entryTime = 3;
	
	strcpy(proc3.process_name,"P3");
	proc3.remainingTime = 3;
	proc3.entryTime = 3;
	
	strcpy(proc4.process_name,"P4");
	proc4.remainingTime = 4;
	proc4.entryTime = 3;
	
	strcpy(proc5.process_name,"P5");
	proc5.remainingTime = 5;
	proc5.entryTime = 3;
	
	strcpy(proc6.process_name,"P6");
	proc6.remainingTime = 6;
	proc6.entryTime = 3;
	
	strcpy(proc7.process_name,"P7");
	proc7.remainingTime = 7;
	proc7.entryTime = 3;
	
	printf("Test Prioirty: %d\n", is_higher_priority(proc1, proc2));
	

	// test init min heap and insert minheap
	Heap* heap = init_heap(SIZE);
	
	pcb_t processes[7] = {proc4, proc2, proc3, proc1, proc6, proc7, proc5};
	for(int j=0; j < 7; j++){
		insert_heap(heap, processes[j]);
	}
	
	print_heap(heap);
	
	pcb_t process;
	for(int i=0; i < 7; i++){
		process = extract_min(heap);
		printf("Extracted Process: %s\n", process.process_name);
		
		//process = get_min(heap);
		//printf("Get Process: %s\n", process.process_name);
		print_heap(heap);
	}
}





