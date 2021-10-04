#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "file_queue_manipulation.c"

/*Function Prototype*/
void first_come_first_serve(Queue *pcb_t_q, Queue *fcfs);
