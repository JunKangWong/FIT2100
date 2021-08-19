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
//void read_file(char *source);
void open_file(int *infile, char *source);
void read_lines(int fd, int line_cnt);
void read_all(int fd);



int main(int argc, char *argv[])
{
  int infile;
  
  // check if invalid number of arguments is given
	if (argc == 2) {
		open_file(&infile, argv[1]);
	}else if (argc == 1){
		open_file(&infile, "sample.txt");
	}else{
		char *outString = "Usage: ./fileutil sourcefile(optional)\n";
		write(2, outString, strlen(outString));
		exit(1);
	}
  
  // perform file based on the number of lines specified.
  read_lines(infile, NUM_OF_LINE);
 
  // close file and terminates successfully.
  close(infile);
  exit(0);
}



/*
Given two arguments infile and source, this function reads file content in the
source path into infile.
*/
void open_file(int *infile, char *source){
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((*infile = open(source, O_RDONLY)) < 0) {
  	char *outString = "Failed to read file\n";
	write(2, outString, strlen(outString));
    exit(1);
  }
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
		if(c == '\n') lines ++;
		
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
