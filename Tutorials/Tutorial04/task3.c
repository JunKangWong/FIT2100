#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
	pid_t pid;
	
	printf("A\n");

	pid = fork();
	
	printf("B\n");
	
	if(pid > 0){
		wait(NULL);
	}
	printf("C\n");
	return 0;
}


/*
Trace the following C code without typing or running it. 
What are the possible outputs for this program?

A
B
B
C
C
*/


