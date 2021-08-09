#include <stdio.h>


void factorial(int n, int *ptr);

int main(){
	// declare accumulator and n.
	int acc = 1, n = 0;
	int *ptr = &acc; // assign a pointer to the accumulator.
	
	// prompt user input
	printf("Please enter a positive integer (including 0): ");
	scanf("%d", &n);
	
	// run factorial function
	factorial(n, ptr);
	
	// output value on accumulator.
	printf("%d\n", acc);
	
	return 0;
}


// define main logic of factorial.
void factorial(int n, int *ptr){
	int i;
	
	for(i = 1; i <= n; i ++)
		*ptr *= i; // update value on pointer.
}




// For personal reference only

/*

// Alternative (Bad)

int main(){
	// declare accumulator and n.
	int *acc, n = 0;
	&acc = 1
	
	// prompt user input
	printf("Please enter a positive integer (including 0): ");
	scanf("%d", &n);
	
	// run factorial function
	factorial(n, acc);
	
	// output value on accumulator.
	printf("%d\n", *acc);
	
	return 0;
}

void factorial(int n, int *ptr){
	int i;
	*ptr = 1;
	for(i = 1; i <= n; i ++)
		*ptr *= i; // update value on pointer.
}


*/

