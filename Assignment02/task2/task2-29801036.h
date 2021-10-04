#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "file_queue_manipulation.c"
#include "pcb_t_priority_queue.c"

#define SIZE 100
#define TIME_QUANTUM 3

void shortest_process_remaining_next(Queue *event_occur, Queue *event_record);
