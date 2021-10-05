#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "file_queue_manipulation.c"

/*Function Prototype*/
void first_come_first_serve(Queue *event_occur, Queue *event_record);
bool schedule_process(Queue* ready, pcb_t *running_process, int current_time);
bool terminate_process(Queue* event_occur, pcb_t *running_process, int current_time);
void to_ready_queue(Queue *ready, Queue *event_occur);
