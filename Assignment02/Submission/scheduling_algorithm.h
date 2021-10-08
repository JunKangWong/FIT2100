/*
Name            : Wong Jun Kang
StudentID       : 29801036
Date created    : 01/10/2021
Last Modified   : 07/10/2021

The header file of scheduling algorithm.c
*/
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "pcb_t_queue.h"
#include "pcb_t_priority_queue_extended.h"


#define SIZE 100


/*Function Prototype*/
void execute_preemptive(const char* source_path, const char* dest_path, priority priority_rule, int t_quant);
void execute_non_preemptive(const char* source_path, const char* dest_path, priority priority_rule);
void preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule, int t_quant);
void non_preemptive_scheduling(Queue *event_occur, Queue *event_record, priority priority_rule);


#endif /* SCHEDULE_H */
