#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 1024

void is_palindrome();


int main(){

	is_palindrome();
	return 0;
}


void is_palindrome(){
	
	char s[1024];
	int n, i, c = 0;

	printf("Please enter a string: \n");
	
	scanf("%s", s);
	
	n = strlen(s);
	
	for(i=0; i < (n/2); i++){
		if(s[i] == s[n-i-1]) c++;
	}
	
	char* outMsg = (c == i) ? "String is a palindrome!\n" : "String is not a palindrome!\n";
	
	printf("%s", outMsg);
}
