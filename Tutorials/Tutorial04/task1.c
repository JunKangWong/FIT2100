#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

	pid_t pid;
	//char *params[] = {"./palindrome", "-aIR", 0};
	char *filename = "sample.txt"; // sample.txt
	
	// fork a child process.
	pid = fork();
	
	// parent process display content from file name denoted in filename variable i.e. "sample.txt"
	if (pid > 0){
		execl("/bin/less", "less", filename, NULL);

	// child process calls echo
	}else if (pid == 0){
		execl("/bin/echo", "echo", "String spawned from the child process", NULL);
	
	}else{
		perror("fork error");
		exit(1);
	}

	return 0;
}
