#include "pcb_t_queue.c"

/*Function Prototype*/
int load_textfile_to_pcb_t_queue(const char* filepath, Queue *pcb_t_q);
void generate_output_file(const char* filepath, Queue *res_queue);
