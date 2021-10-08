# Name          : Wong Jun Kang
# Student ID    : 29801036
# Date Added    : 07/10/2021
# Date Modified : 08/10/2021
# Make file for task1, task2 and task3

# c files declarations
OBJS = pcb_t_queue.c pcb_t_priority_queue_extended.c pcb_t_file_io.c change_process_state.c scheduling_algorithm.c
TASK1 = task1-29801036.c
TASK2 = task2-29801036.c
TASK3 = task3-29801036.c

#shared variables
CC = gcc
LFLAGS = -Wall

all: task1 task2 task3

task1: $(OBJS) $(TASK1)
	$(CC) $(LFLAGS) $(OBJS) $(TASK1) -o task1
task2: $(OBJS) $(TASK2)
	$(CC) $(LFLAGS) $(OBJS) $(TASK2) -o task2
task3: $(OBJS) $(TASK3)
	$(CC) $(LFLAGS) $(OBJS) $(TASK3) -o task3
clean:
	rm -f *.o task1 task2 task3 result*.txt
