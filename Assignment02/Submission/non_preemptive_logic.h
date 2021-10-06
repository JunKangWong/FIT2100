#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "file_queue_manipulation.c"
#include "pcb_t_priority_queue_extended.c" // this has to be called before change_process_state.c for queue structure.
#include "change_process_state.c"

#define SIZE 100


/*Function Prototype*/
void execute_non_preemptive(const char* source_path, const char* dest_path, priority priority_rule);
void non_preemptive_tick(Queue *event_occur, Queue *event_record, priority priority_rule);
