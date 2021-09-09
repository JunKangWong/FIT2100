#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	int limit = 10;
	
	printf("FIT2100\n");
	
	for (int i = 0; i < limit; i++){
		printf("Operating\n");
		fork();
	}
	
	printf("Systems\n");
	return 0;
}



/*

Trace the following C code carefully without typing or running it. Find out how many
times the program prints "FIT2100", "Operating" and "Systems". What about when limit
= 1 and limit = 3? Can you observe any patterns? (You may want to draw a simple tree-like diagram)
to understand the parent-child hierarchy of the proccesses spawned.)

limit = 2

				Root
				Operating * 2
				Systems * 1
		Child1			Child2
		Operating * 1	Systems * 1
		Systems * 1
	Child3
	Systems * 1


<<Ordering>>

Operating
Operating
Operating
Systems
Systems
Systems
Systems

*/
