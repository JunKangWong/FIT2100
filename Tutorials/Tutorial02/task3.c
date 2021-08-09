#include <stdio.h>
#include <stdlib.h>


// function prototype
int *find_largest(int the_array[], int num_elements);


int main(){
	int i, sum = 0, n = 0;
	

	printf("How many numbers to add? ");
	scanf("%d", &n);
	
	// declare dynamic array based on input size.
	//int array = (int*) malloc (sizeof(int) * n);
	//int *iptr = array;
	int *iptr = (int*) malloc (sizeof(int) * n);
	int *ptr = iptr; // is this required?
	
	for(i = 1; i <= n; i ++){
		printf("Enter number %d: ", i);
		scanf("%d", iptr++);
	}
	
	// print the largest value
	printf("The largest value in the array is %d\n" , *(find_largest(ptr, n)));

	return 0;

}


// method 1 (increment i only)
int* find_largest(int the_array[], int num_elements){
	int i;
	int *new_ptr;
	
	for(i=0; i < num_elements; i++){
		new_ptr = (the_array[i] > *new_ptr) ? &the_array[i] : new_ptr;
	}
	return new_ptr; // return pointer of largest element
}



/*

// method 2 (increment pointer *ptr together)
int* find_largest(int the_array[], int num_elements){
	int i;
	int *new_ptr;
	
	for(i=0; i < num_elements; i++){
		new_ptr = (*the_array > *new_ptr) ? the_array : new_ptr;
		the_array ++;
	}
	return new_ptr; // return pointer of largest element

}

*/







