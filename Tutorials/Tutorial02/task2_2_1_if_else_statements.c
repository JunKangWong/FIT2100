#include <stdio.h>


/*How do we pass in an array / string (array of characters)*/


// function prototype
void format_hour(int *hour, char *meridiem);
int is_valid(int *hour, int *min);



int main(){

	int hour = 0, min = 0;
	char meridiem[2] = "NA";
	char *p = meridiem;

	printf("Please enter a time in 24-hour format (hh:mm): ");
	scanf("%d:%d", &hour, &min);
	
	format_hour(&hour, p);
	
	printf("%d:%2d %s", hour, min, meridiem);
	

}



// This function format hour in 12 hour format
void format_hour(int *hour, char *meridium)
{	
	char string[2];
	

	*hour = (*hour >= 13) ? (*hour % 13 + 1) : *hour;
	string = (*hour >= 13) ? "PM" : "AM";
	
	while ((*meridiem++ = *string++) != '\0');
	
}


// not yet test
int is_valid(int *hour, int *min){
	
	int valid = 1;
	
	if (*hour >= 24 || *hour < 0 || *min >= 60 || *min < 0)
		printf("invalid input");
		valid = 0;
	
	return valid;
}





