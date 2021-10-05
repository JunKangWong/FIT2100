#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "file_queue_manipulation.c"
#include "pcb_t_priority_queue.c"

#define SIZE 100
#define TIME_QUANTUM 3


/*Function Prototype*/
void shortest_process_remaining_next(Queue *event_occur, Queue *event_record);
bool schedule_process(Heap *ready, pcb_t *running_process, int current_time);
bool terminate_process(Queue *event_record, pcb_t *running_process, int current_time);
bool preempt_process(Heap *ready, pcb_t *running_process, int current_time);
void to_ready_queue(Heap *ready, Queue *event_occur);
