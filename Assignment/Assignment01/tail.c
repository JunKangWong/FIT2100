/* task4.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);


#include <stdio.h> 
#include <stdbool.h>
#include <libgen.h>



void open_read_file(int *infile, char *source);
void open_write_file(int *outfile, char *source);
void head(int infile, int outfile, int line_cnt);
void tail(int infile, int outfile, int line_cnt);
int count_line(int infile, size_t limit);

int main(){
	int infile, outfile;
	
	char *source = "/home/student/Documents/FIT2100/Assignment01/sample.txt";


	open_read_file(&infile, source);
	printf("number of line: %d\n",count_line(infile, 20));
	
	
	// Test tail
	tail(infile, 1, 17); // print 3 to 19
	printf("\n");
	tail(infile, 1, 18); // print 2 to 19
	printf("\n");
	tail(infile, 1, 19); // print 19
	printf("\n");
	tail(infile, 1, 20); // print 18
	printf("\n");
	tail(infile, 1, 1000); // print 18
	
	close(infile);
	
	return 0;
}


void open_write_file(int *outfile, char *source){

	if ((*outfile = open(source, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
	  	char *outString = "Failed to open write file\n";
		write(2, outString, strlen(outString));
		exit(1);
	}
}


/*
Given two arguments infile and source, this function reads file content in the
source path into infile.
*/
void open_read_file(int *infile, char *source){
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((*infile = open(source, O_RDONLY)) < 0) {
  	char *outString = "Failed to open read file\n";
	write(2, outString, strlen(outString));
    exit(1);
  }
}



void head(int infile, int outfile, int line_cnt){ // change line_cnt to head
	size_t lines = 0;
	char c;

	while(read(infile, &c, 1) > 0 && lines < line_cnt){
	
		// write character by character to terminal
		write(outfile, &c, 1);
		
		// increment when encounter '\n'.
		if(c == '\n') lines ++;
	}
}



void tail(int infile, int outfile, int limit){
	int i = -1, lines = 0;
	char c;
	

	while(lseek(infile, i * sizeof(char), SEEK_END) != -1 && lines <= limit){
	
		//lseek(infile, i * sizeof(char) , SEEK_END);
		read(infile, &c, 1);
		
		if (c == '\n') lines ++;
		i--;
	}
	
	//write character by character to terminal
	lseek(infile, (long) (++i) * sizeof(char), SEEK_END);
	head(infile, outfile, limit+1);
}



// i.e. return number of line in file if line < limit else return limit
int count_line(int infile, size_t limit){
	size_t lines = 0;
	char c;
	
	lseek(infile, 0 , SEEK_SET);
	while(read(infile, &c, 1) > 0 && lines < limit){
		// increment when encounter '\n'.
		if(c == '\n') lines ++;
	}
	return lines;
}











