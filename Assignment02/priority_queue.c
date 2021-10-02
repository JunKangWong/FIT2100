#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task1-29801036.h"


#define 100

/*
1) write a malloc versin then convert to stack version later on to try out
1) test is_higher_priority
3) test swap
4) 

Referenced and modified from:

*/


typedef struct{
	pcb_t *arr;
	int size, capacity; // current size and maximum capacity;
}MinHeap;



int parent(int i){
	return (i-1)/2;
}


int left_child(int i){
	return (2*i + 1);
}

int right_child(int i){
	return (2*i + 2);
}

int get_min(MinHeap* heap){
	return heap -> arr[0];
}


MinHeap* initialise_minHeap(int capacity){
	MinHeap* minheap = (MinHeap*) calloc (1, sizeof(MinHeap));
	minheap->arr = (pcb_t*) calloc (capacity, sizeof(pcb_t));
	minheap->capacity = capacity;
	minheap->size = 0;
	return minheap;
}


MinHeap* insert_minheap(MinHeap* heap, int element){

	if(heap->size == heap->capacity){
		fprintf(stderr, "maximum capacity reached for min heap!");
		return heap;
	}
	
	// increment size first
	// then, insert element as the last element of the heap.
	heap->size++; 
	heap->arr[heap->size -1] = element;
	
	// keep swapping the element upwards until it reaches the root.
	int curr = heap->size - 1;
	
	// while not root and child has a higher priority than children
	while(curr > 0 && is_higher_priority(heap->arr[curr],heap->arr[parent(curr)])){
		swap(heap, parent(curr), curr); // swap parent and child in the heap.
		curr = parent(curr);
	}
}

/*Swap current with its parent*/
void swap(MinHeap* heap, int x, int y){
	int temp = heap->arr[x];
	heap->arr[x] = heap->arr[y];
	heap->arr[y] = temp;
}

void rise(){
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





