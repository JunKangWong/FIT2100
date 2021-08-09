#include <stdio.h>
#include <stdlib.h>



//typedef unsigned long int size_int;

// function prototype
void *malloc(size_t size);



int main(){
	int i, sum = 0, n = 0;

	printf("How many numbers to add? ");
	scanf("%d", &n);
	
	// declare dynamic array based on input size.
	//int array = (int*) malloc (sizeof(int) * n);
	//int *iptr = array;
	int *iptr = (int*) malloc (sizeof(int) * n);
	int *test = iptr; 		// for method 1
	
	for(i = 1; i <= n; i ++){
		printf("Enter number %d: ", i);
		scanf("%d", iptr++);
	}
	
	/*
	// Method 1 (The pointer way)
	for(i = 1; i <= n; i ++){
		sum += *test;
		test++;
	}
	*/
	
	// Method 2 (The array way)
	for(i = 0; i < n; i ++){
		sum += test[i];
	}
	
	/*
	// Method 3 (Reverse pointer way)
	for(i = 1; i <= n; i ++){
		iptr --;
		sum += *iptr;
	}
	*/
	
	// what is the normal way to do this?
		// Do we always have to define another pointer that point at the front of the array?
	
	printf("%d\n", sum);

	return 0;
	
}



