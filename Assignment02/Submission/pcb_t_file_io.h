/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

Header file of pcb_t_file.io
*/
#include "pcb_t_queue.c"

#define PATH_LENGTH 1024


/*Function Prototype*/
int load_textfile_to_pcb_t_queue(const char* filepath, Queue *pcb_t_q);
void print_event(pcb_t cur_event);
bool store_path(char** buffer, const char* str, bool path_not_provided);
void generate_output_file(const char* filepath, Queue *res_queue);
