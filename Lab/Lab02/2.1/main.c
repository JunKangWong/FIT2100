#include <stdio.h>


int main(){
	int a = 0, b = 0;
	
	
	printf("Please enter number 1: ");
	scanf("%d", &a);
	
	printf("Please enter number 2: ");
	scanf("%d", &b);
	
	printf("Addition: %d\nSubtraction: %d\nMultiplication: %d\nDivision: %d\n" 
	, addition(a,b), subtraction(a,b), multiplication(a,b), division(a,b));
	
	return 0;
}



