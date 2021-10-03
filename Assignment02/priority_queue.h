#include <stdio.h>

typedef struct{
	pcb_t *arr;
	int size, capacity; // current size and maximum capacity;
}Heap;




/*Function Prototype*/

int parent(int i);
int left_child(int i);
int right_child(int i);
pcb_t get_min(Heap* heap);
Heap* init_heap(int capacity);
Heap* insert_heap(Heap* heap, pcb_t elem);
void swap(Heap* heap, int x, int y);
bool is_higher_priority(pcb_t x, pcb_t y);
void free_heap(Heap* heap);
void print_heap(Heap* heap);
Heap* heapify(Heap* heap, int index);
Heap* delete_minimum(Heap* heap);
pcb_t extract_min(Heap* heap);
