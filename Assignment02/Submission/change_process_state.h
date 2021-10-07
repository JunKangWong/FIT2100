/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

The header file of change_process_state.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool schedule_process(Heap *ready, pcb_t *running_process, int current_time);
bool terminate_process(Queue *event_record, pcb_t *running_process, int current_time);
void to_ready_queue(Heap *ready, Queue *event_occur);
bool preempt_process(Heap *ready, pcb_t *running_process, int current_time);
