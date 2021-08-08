#include <stdio.h>


// function prototype
void format_hour(int *hour);
int is_valid(int *hour, int *min);



int main(){

	int hour = 0, min = 0;

	printf("Please enter a time in 24-hour format (hh:mm): ");
	scanf("%d:%d", &hour, &min);
	
	format_hour(&hour);
	printf("%d:%2d %s\n", hour, min, (hour >= 13) ? "PM" : "AM");
	

}



// This function format hour in 12 hour format
void format_hour(int *hour)
{	
	*hour = (*hour >= 13) ? (*hour % 13 + 1) : *hour;
}


// not yet test
int is_valid(int *hour, int *min){
	
	int valid = 1;
	
	if (*hour >= 24 || *hour < 0 || *min >= 60 || *min < 0)
		printf("invalid input");
		valid = 0;
	
	return valid;
}





