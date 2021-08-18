/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);


/*Function prototype*/
void read_lines(int fd, int line_cnt);
void read_all(int fd);



int main()
{
  int infile;

  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((infile = open("sample.txt", O_RDONLY)) < 0) {
    exit(1);
  }
  
  // perform file based on the number of lines specified.
  read_lines(infile, NUM_OF_LINE);
 
  // close file and terminates successfully.
  close(infile);
  exit(0);
}



/*
Given the file descriptor(fd) and line count (line_cnt)
This function reads
*/
void read_lines(int fd, int line_cnt){
	size_t lines = 0;
	char c;
	
	while(read(fd, &c, 1) > 0 && lines < line_cnt){
	
		// write character by character to terminal
		write(1, &c, 1);
		
		// increment when encounter '\n'.
		if(c == '\n'){
			lines ++;
		}
	}
	
}


/*Given a file descriptor this function reads all content of the file*/
void read_all(int fd){
	int n = 0;
	char buffer[BUFFERSIZE];

  //read() returns the number of byte read
   	while((n = read(fd, buffer, BUFFERSIZE)) > 0){
     	write(1, buffer, n);
   }
}


      
