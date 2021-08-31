#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void count (int start, char ch);

int main(int argc, char *argv[]) {
    int pid;
    int start=0;

    pid = fork();       /* fork a child process */

    if(pid > 0) {       /* parent continues here  */
        count(start, 'P');
        wait(NULL);     /* to get printing done before shell prompt */
    } else if(pid == 0) {    /* child got here */
        //execl("/bin/ls", "ls", "-l", NULL); /* execute ls command */
        execl("/home/student/Documents/FIT2100/LAB03/palindrome", "palindrome", NULL); /* execute ls command */
    } else {            /* there is a problem with fork */
        perror("Failed to fork a process\n");
        exit(1);
    }
}

void count (int start, char ch) {
    int i, j;
    for(i = start; i < 10; i++) {
        for(j = 0; j < 1000000; j++);  /*delay*/
        printf("Message from %c process at the %dth iteration \n", ch, i);
    }
}
