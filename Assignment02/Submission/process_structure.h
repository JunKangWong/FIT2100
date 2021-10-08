/*
Name			: Wong Jun Kang
StudentID		: 29801036
Date created	: 01/10/2021
Last Modified	: 07/10/2021

The process structure of pcb_t processes.
*/

#ifndef P_STRUCTURE_H
#define P_STRUCTURE_H

// assume name of process is never more than 10 characters in length and does not contain spaces
#define PROCESS_NAME_SIZE 11
#define START_TIME 0

/*Special enumerated data type for process state*/
typedef enum {
	READY, RUNNING, TERMINATED
}process_state_t;



typedef struct {
	char process_name[PROCESS_NAME_SIZE]; // A string that identifies the process
	int event_time; // time when an event occur.
	
	/*Time are measured in seconds*/
	int entryTime;				// The time process entered system
	int terminateTime;			// process terminated completed
	int firstServedTime;		// TIme when the process is first served.
	int serviceTime;			// The total CPU time required by the process
	int remainingTime;			// Remaining service time until completion
	int deadline;
	process_state_t state;		// current process state (e.g. READY) as specified in the enum above

}pcb_t;


#endif /* P_STRUCTURE_H */
