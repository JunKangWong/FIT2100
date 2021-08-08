#include <stdio.h>
#include <string.h>

void num_to_eng(int num, char *ptr);

int main(){
	char str[10] = "test";
	char *ptr = str;
	int num = 9;
	
	
	num_to_eng(num, ptr);
	printf("%s\n", str);
	
}


// ten and eleven are exception
void num_to_eng(int num, char *ptr){

	printf("%d\n", num);
	char string[10];
	int i = 0;
	
	switch(num)
	{
		case 1:
			printf("test1\n");
			strcpy(string, "one");
		case 2:
			printf("test2\n");
			strcpy(string, "two");
		case 3:
			printf("test3\n");
			strcpy(string, "three");
		case 4:
			printf("test4\n");
			strcpy(string, "four");
		case 5:
			printf("test5\n");
			strcpy(string, "five");
		case 6:
			printf("test6\n");
			strcpy(string, "six");
		case 7:
			printf("test7\n");
			strcpy(string, "seven");
		case 8:
			printf("test8\n");
			strcpy(string, "eight");
		case 9:
			printf("test9\n");
			strcpy(string, "nine");
		default:
			printf("test_default\n");
			strcpy(string, "N/A");
	}
	
	// update string for output
	while ((*ptr++ = string[i]) != '\0') i++;

}





/*

void special_case(int num){

	char string[10];
	
	switch(num)
	{
		case 10:
			string = "ten"
		case 11:
			string = "eleven";
		case 12:
			string = "twelve";
		default:
			string = "N/A";
	}
}



char num_to_eng(){
	
	char string[10];
	
	switch(num)
	{
		case 1:
			string = "teen" // 
		case 2:
			string = "twenty";
		case 3:
			string = "thirty";
		case 4:
			string = "forty";
		case 5:
			string = "fifty";
		case 6:
			string = "sixty";
		case 7:
			string = "seventy";
		case 8:
			string = "eighty";
		case 9:
			string = "ninty";
		default:
			string = "N/A";
	}

}


void solution(){


}
*/






