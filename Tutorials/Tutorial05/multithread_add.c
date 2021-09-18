/* multithread_add.c */
#include <stdio.h>      /* standard I/O routines */
#include <pthread.h>    /* pthread functions and data structures */
#include <unistd.h>     /* we will use sleep() later on in prac */
#include <stdlib.h>     /* needed for exit() function */


/*global variable*/
int sum;

/*Function prototype*/
void* print_hello(void* t);


/* Like any C program, program's execution begins in main */
int main(int argc, char* argv[]) {
  int rc, i, x = atoi(argv[1]);      /* data passed to the new thread */
  int threadNum[x];
  pthread_t thread[x];
  
  /* create a new thread that will execute 'print_hello()' */
  for(i=1; i <= x; i++){
  	threadNum[i] = i;
    rc = pthread_create(&thread[i], NULL, print_hello, &threadNum[i]);
    
    if(rc) {    /* could not create thread */
      printf("\n ERROR: return code from pthread_create is %d by thread %ld \n", rc, thread[i]);
      exit(1);
    }else{
    	printf("I am thread %ld. Created new thread (%ld) in iteration %d. Current sum: %d\n", pthread_self(), thread[i], i, sum);
    }
    
    // for every 4 iterations sleep for 1 second
    if(i % 4 == 0) sleep(1);
  }
  pthread_exit(NULL);     /* terminate the thread */
}


//This function is to be executed by the new thread 
void* print_hello(void* t) {
  int my_t = *(int *)t; // data received by thread

  pthread_detach(pthread_self());
  sum += my_t;
  printf("Hello from thread (%ld) - I was created in iteration %d. Current sum: %d\n", pthread_self(), my_t, sum);

  pthread_exit(NULL);     // terminate the thread 
}
