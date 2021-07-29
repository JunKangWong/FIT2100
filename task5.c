#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 6

/*Task 5*/

/*function prototype*/
void generate_random_numbers();
void generate_random_numbers2();


/*function driver*/
int main()
{
generate_random_numbers();
return 0;
}

/*main solution*/
void generate_random_numbers()
{
	int i;
	time_t t;
	
	srand(time(NULL));
	
	for(i=0; i < COUNT; i++){
	
		printf("%d\n", rand());
	}
	

}









void generate_random_numbers2()
{
	int i;
	time_t t;
	
	srand((unsigned) time(&t));
	
	for(i=0; i < COUNT; i++){
	
		printf("%d\n", rand());
	}
	

}
