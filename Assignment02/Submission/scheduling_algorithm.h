/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

The header file of scheduling algorithm.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "process_structure.h" // this has to be called first for pcb_t structures.
#include "pcb_t_file_io.c"
#include "pcb_t_priority_queue_extended.c" // this has to be called before change_process_state.c for queue structure.
#include "change_process_state.c"

#define SIZE 100
#define TIME_QUANTUM 3


typedef enum {
	PREEMPTIVE, NON_PREEMPTIVE
}schedule_mode;



/*Function Prototype*/
void scheduling_algorithm(const char* source_path, const char* dest_path, priority priority_rule, schedule_mode mode);
void preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule);
void non_preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule);

