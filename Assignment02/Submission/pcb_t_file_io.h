/*
Name            : Wong Jun Kang
StudentID       : 29801036
Date created    : 01/10/2021
Last Modified   : 07/10/2021

Header file of pcb_t_file.io
*/


#ifndef PCB_T_FILE_IO_H
#define PCB_T_FILE_IO_H

#include <stdbool.h>
#include "process_structure.h"
#include "pcb_t_queue.h"


/*Function Prototype*/
int load_textfile_to_pcb_t_queue(const char* filepath, Queue *pcb_t_q);
void print_event(pcb_t cur_event);
void generate_output_file(const char* filepath, Queue *res_queue);
bool store_path(char** buffer, const char* str, bool path_not_provided);



#endif /* PCB_T_FILE_IO_H */
