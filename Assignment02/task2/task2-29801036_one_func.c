#include "task2-29801036.h"

int main(){
	Queue event_occur, event_record;
	initialise_queue(&event_occur);
	initialise_queue(&event_record);

	// load textfile "processes.txt" into event_occur queue for processing.
	load_textfile_to_pcb_t_queue("processes2.txt", &event_occur);
	
	// simulates shortest process remaining next scheduler and record event into event_record queue.
	shortest_process_remaining_next(&event_occur, &event_record);
	
	// generate an output file according to the recorded events in event_record queue.
	generate_output_file("results-task2.txt", &event_record);
}



void shortest_process_remaining_next(Queue *event_occur, Queue *event_record){
	int current_time = 0;
	bool completed = true;
	int active_process = 0;
	pcb_t running_process;
	pcb_t arrive;
	int time_quant;
	
	// initialise a priority queue (min heap) based on remainingTime.
	Heap* ready = init_heap(SIZE);
	
	// while there are still process to be loaded.
	// This outer loop simulates clock tick.
	while(event_occur->item_count > 0 || active_process > 0){
		
		// simulates arrival of process
		while(event_occur->value[(event_occur->front)+1].entryTime == current_time){
			arrive = dequeue(event_occur);
			arrive.event_time = current_time; // record time of event occurence.
			insert_heap(ready, arrive);			// insert newly arrived process into ready queue.
			active_process ++;
			
			print_event(arrive);
		}
		
		// simulate running of processes
		if (!completed){
			running_process.remainingTime --;
			time_quant --;
		
			if(running_process.remainingTime == 0){
				active_process --;
				running_process.state = TERMINATED;
				running_process.terminateTime = current_time;
				enqueue(event_record, running_process);
				completed = true;
				
			}else if(time_quant == 0){
				// if running process is still the highest priority process after time quantum is over.
				// continue to run.
				if(is_higher_priority(running_process, get_root(ready))){
					time_quant = TIME_QUANTUM; // reset time quantum
				}else{
					// insert running process back to priority queue if its not completely terminated.
					insert_heap(ready, running_process);
					running_process.state = EXIT; // READY?
					completed = true;
				}
			}
			// record event if process completed or process preempted.
			if(completed){
				running_process.event_time = current_time;
				print_event(running_process);
			}
		}
		
		// simulates scheduling of process
		// if current process completes running andready queue has element to be scheduled.
		if(ready->size > 0 && completed){
			time_quant = TIME_QUANTUM; // reset time quantum
			
			running_process = extract_root(ready); 
			
			// update firstServedTime only when remainingTime equals to firstServedTime.
			running_process.firstServedTime = (running_process.remainingTime == running_process.serviceTime) ? current_time : running_process.firstServedTime;
			running_process.state = RUNNING;
			running_process.event_time = current_time;
			completed = false;
			
			// record occurence of event
			print_event(running_process);
		}
		
		// clock tick by 1 second
		current_time ++;
	}
	// free up memory of ready queue.
	free_heap(ready);
}

