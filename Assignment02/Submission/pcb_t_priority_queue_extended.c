#include "pcb_t_priority_queue_extended.h"


//#define SIZE 100
/*
Referenced and modified from:
Is_Higher...
This Priority Heap Min Heap property.
The is higher priority function can be modified to easily alter the behaviour to make the heap max heap.
*/

Heap* init_heap(int capacity, priority operation_mode){
	Heap* heap = (Heap*) calloc (1, sizeof(Heap));
	heap->arr = (pcb_t*) calloc (capacity, sizeof(pcb_t));
	heap->capacity = capacity;
	heap->size = 0;
	heap->priority_rule = operation_mode;
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

pcb_t get_root(Heap* heap){
	return heap -> arr[0];
}


/*Swap current with its parent*/
void swap(Heap* heap, int x, int y){
	pcb_t temp = heap->arr[x];
	heap->arr[x] = heap->arr[y];
	heap->arr[y] = temp;
}


bool is_higher_priority(Heap* heap, pcb_t x, pcb_t y){
	bool is_x_higher_priority;
	
	switch(heap->priority_rule){
		case FIRST_COME_FIRST_SERVE:
			is_x_higher_priority = first_come_first_serve(x, y);
			break;
		case SHORTEST_REMAINING_TIME:
			is_x_higher_priority = shorter_remaining_time_first(x, y);
			break;
		case MAXIMISE_DEADLINE:
			is_x_higher_priority = maximise_processes(heap, x, y);
			break;
	}
	return is_x_higher_priority;
}



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



bool maximise_processes(Heap* heap, pcb_t x, pcb_t y){
	int current_time = heap->lifetime_counter;
	int X = (x.entryTime + x.deadline) - current_time; 
	int Y = (y.entryTime + y.deadline) - current_time;
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

bool maximise_processes(Heap* heap, pcb_t x, pcb_t y){
	int current_time = heap->lifetime_counter;
	int X = (x.entryTime + x.deadline) - current_time; 
	int Y = (y.entryTime + y.deadline) - current_time;
	bool X_pass = deadline_test(x, current_time);
	bool Y_pass = deadline_test(y, current_time);
	
	// if both process x and process y passes the deadline test
	// meaning that they both can meet deadline if scheduled now.
	if (X_pass && Y_pass){
		// if x has a sooner deadline
		if(X <= Y){
			// if y can meets its deadline if x executes first
			if (deadline_test(y, current_time + x.service_time)){
				// as 1 of the processes is guaranteed not to meet its deadline
				//executes x first
				return true;
			}else {
				// Since we have to have to "sacrifice" one process
				// as y cannot meet deadline if execute after x
				// sacrifice the one with longer serviceTime.
				return x.serviceTime < y.serviceTime;
			}
		}else{
			// if y has a sooner deadline
			// if x can meets its deadline if y executes first
			if (deadline_test(x, current_time + y.service_time)){
				// as 1 of the processes is guaranteed not to meet its deadline
				//executes y first
				return false;
			}else {
				// Since we have to have to "sacrifice" one process
				// as y cannot meet deadline if execute after x
				// sacrifice the one with longer serviceTime.
				return y.serviceTime < x.serviceTime;
			}
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
*/


//can complete before deadline
bool deadline_test(pcb_t p, int current_time){
	return current_time + p.serviceTime <= p.entryTime + p.deadline;
}





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
}



/*
Performing heapify recursively.
Rearranging the heap as to maintain the heap property.
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




Heap* delete_root(Heap* heap){
	// if heap is empty
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


pcb_t extract_root(Heap* heap){

	// get root item then delete the item.
	pcb_t process = get_root(heap);
	delete_root(heap);
	return process;

}


void print_heap(Heap* heap){

	printf("pcb_t Heap:\n");
	
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
May implement if require

MinHeap* delete_element(MinHeap* heap, int index){

}

void rise(){

}




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
	

	// test init heap and insert heap
	Heap* heap = init_heap(100);
	
	pcb_t processes[7] = {proc4, proc2, proc3, proc1, proc6, proc7, proc5};
	for(int j=0; j < 7; j++){
		insert_heap(heap, processes[j]);
	}
	
	print_heap(heap);
	
	pcb_t process;
	for(int i=0; i < 7; i++){
		process = extract_root(heap);
		printf("Extracted Process: %s\n", process.process_name);
		
		//process = get(heap);
		//printf("Get Process: %s\n", process.process_name);
		print_heap(heap);
	}
	
	free_heap(heap);
}

*/


