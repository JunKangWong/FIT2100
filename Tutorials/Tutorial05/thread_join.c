/* thread_join.c */

#include <stdio.h>      /* standard I/O routines */
#include <pthread.h>    /* pthread functions and data structures */
#include <unistd.h>
#include <stdlib.h>     /* needed for exit function */

/* This function is to be executed by the new thread */
void* print_hello(void* data) {
  pthread_t tid = *data;   /* data received by thread */

  pthread_join(tid, NULL);            /* wait for thread: tid */

  printf("Hello from new thread %lu - got %lu\n", pthread_self(), tid);
  pthread_exit(NULL);                 /* terminate the thread */
}

int main(int argc, char* argv[]) {
  int rc;                             /* value returned from thread creation*/
  pthread_t thread_id, parent_id;     /* thread IDs */

  parent_id = pthread_self();
  rc = pthread_create(&thread_id, NULL, print_hello, &parent_id);
  
  if(rc) {    /* could not create thread */
    printf("\n ERROR: return code from pthread_create is %d \n", rc);
    exit(1);
  }

  sleep(1);
  printf("\n Created new thread (%lu) ... \n", thread_id);
  pthread_exit(NULL);
}
