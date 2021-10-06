#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool schedule_process(Heap *ready, pcb_t *running_process, int current_time);
bool terminate_process(Queue *event_record, pcb_t *running_process, int current_time);
void to_ready_queue(Heap *ready, Queue *event_occur);
bool preempt_process(Heap *ready, pcb_t *running_process, int current_time);
