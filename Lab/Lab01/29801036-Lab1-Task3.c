/*
3.3 Task 3 (Extension: 0 marks) 
task2.c
Fix the program from Task 2, so that it does what it claims to the user it can do.
*/

#include <stdio>
#define SIZE 10

int main(){
	char string[SIZE];
	
	printf("Enter a word, up to 10 characters long: ");
	scanf("%s", string);

	printf("You entered %s\n", string);
}
