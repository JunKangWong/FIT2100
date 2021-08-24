/*

Name			: Wong Jun Kang
Student ID		: 29801036
Date created	: 19/08/2021
Last modified	: 24/08/2021

File path manipulation functions 

This c module contains file manipulation functions including path concatenation function,
openfile functions and copyfile functions. 

*/

#include "29801036_file_manipulations.h"


/*

Given a string and a buffer this function Stores str (String) in to buffer.

Arguments

buffer		: a char pointer that is used to store dynamic (malloc) string.
str			: a char* string to be stored
reallocate	: a bool indicate the on/off of reallocate mode.
			  true indicates the buffer is already allocated hence use realloc 
			  instead of malloc.
			  
Return		: bool true if no error occurs else false.
			  

*/
bool store_str(char **buffer, const char* str, const bool reallocate){
	// Check if reallocate mode is activated
	if(reallocate){
		*buffer = (char *) realloc(*buffer, strlen(str) + 1);
	}else{
		*buffer = (char *) malloc(strlen(str) + 1);
	}
	
	if (*buffer == NULL) {
	
		const char *errorMsg = "ERROR: Pointer is NULL after memory allocation.\n";
		write(2, errorMsg, strlen(errorMsg));
		
		return false;
	}
	
	strcpy(*buffer, str);
	
	return true;
}



/*

Given a destination directory and filename, this function concatenate the
destination directory with the filename and store it into the destination path 
buffer.

Arguments
dest_dir	: A char string (char*) that stores the name of the destination directory.
filename 	: A char string (char*) that stores the filename of the file to copy.
dest_path 	: A char buffer (char**) that stores the result of the concatenated string.
			  name of destination directory + filename.


Return		: bool true if no error occur else return false.

*/
bool get_path(const char *dir, const char *filename, char **path){
	char last_c = dir[strlen(dir)-1];

	// Check if last character of destination path is '/' if not add manually.
	if (last_c == '/'){
		*path = (char *) malloc(strlen(dir) + strlen(filename) + 1);
		
		if (*path == NULL) {
		
			const char *errorMsg = "ERROR: Pointer is NULL after memory allocation.\n";
			write(2, errorMsg, strlen(errorMsg));
			
			return false;
		
		}
		strcpy(*path, dir);
		strcat(*path, filename);
		
	}else{ // '/' doesnt already exists
		*path = (char *) malloc(strlen(dir) + strlen(filename) + 2);
		
		if (*path == NULL) {
		
			const char *errorMsg = "ERROR: Pointer is NULL after memory allocation.\n";
			write(2, errorMsg, strlen(errorMsg));
			
			return false;
		}
		
		
		strcpy(*path, dir);
		strcat(*path, "/");		// add a '/' between dir and filename.
		strcat(*path, filename);
	}
	
	return true;
}




/* File manipulation functions */



/*

Given two arguments outfile and source, this function opens the file in write mode
and if the file doesn't already exist create a new file. However, if the directory
path doesnt exist write errorMsg to stdout and return false. If the file already 
exist at the filepath write errorMsg and return false. False indicates that there
is error while opening the file.

Arguments
Outfile		: int* file desctiptor that points to the sfile to be written into
dest		: const char* destination path to open and write file to.

Return		: Bool true if no error occur else return false.

*/
bool open_write_file(int *outfile, const char *dest){
	if ((*outfile = open(dest, O_WRONLY | O_CREAT | O_EXCL , 0664)) < 0){
		
		// Check for different error type and print corressponding error message.
		// file already exist.
		if(errno == EEXIST){
		
			const char *errorMsg = "ERROR: File with the same name already exists.\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
		
		// file destination directory does not exists
		}else if(errno == ENOENT){
		
			const char *errorMsg = "ERROR: Destination directory does not exist.\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
			
		// other reasons
		}else{ 
		
			const char *errorMsg = "Failed to open write file\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
		}
	}

	return true;
}


/*
Given two arguments infile and source, this function reads file content in the
source path into infile in readonly mode. Return false if file path doesnt exists.

infile 	: int* file descriptor that points to the file read.
source	: the source path we read the path from.

Return	: bool true if no error occurs else return false.

*/
bool open_read_file(int *infile, const char *source){
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((*infile = open(source, O_RDONLY)) < 0) {
  
  		// Check for different error type and print corressponding error message.
	  	if(errno == ENOENT){
			// source file doesnt exist.
	  		const char *errorMsg = "ERROR: Source file or directory does not exist.\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
	  	
	  	}else{ // other reasons
	  	  	const char *outString = "ERROR: Failed to open read file\n";
			write(2, outString, strlen(outString));
			return false;
	  	}
  }
  return true;
}



/*
Given an infile and an outfile descriptor this file writes the content from the
infile into the outfile. The number of line to write is determined by the "limit"
argument.

Arguments
infile		: const int file descriptor of file to read
outfile 	: const int file descriptor of file to write to.
limit		: const int number of line to write.

*/
void head(const int infile, const int outfile, const int limit){ 
	size_t lines = 0;
	char c;

	// read character by character and stop when line reaches limit.
	while(read(infile, &c, 1) > 0 && lines < limit){
	
		// write character by character to terminal
		write(outfile, &c, 1);
		
		// increment when encounter '\n'.
		if(c == '\n') lines ++;
	}
}



/*
Given an infile and an outfile descriptor this file writes the content from the
infile into the outfile. The number of line to write is determined by the "limit"
argument.

Arguments
infile		: const int file descriptor of file to read
outfile 	: const int file descriptor of file to write to.
limit		: const int number of line to write.

*/
void tail(const int infile, const int outfile, const int limit){
	int i = -1, lines = 0;
	char c;
	
	// go through the infile from the end of the file in reverse order until 
	// lines reaches limit.
	while(lseek(infile, i * sizeof(char), SEEK_END) != -1 && lines <= limit){
		
		// read character by character
		read(infile, &c, 1);
		
		if (c == '\n') lines ++;
		i--;
	}

	//after located the start point, write character by character to terminal
	lseek(infile, (long) i+2 * sizeof(char), SEEK_END);
	lseek(outfile, 0, SEEK_SET);
	print_all(infile, outfile);
}


/*

Given an infile and an outfile descriptor this file writes the content from the
infile into the outfile. Unlike head, this function print all content from the 
file without needing the user to specify any limit. Also, a buffer size of 1024
was defined for more effective reading and writing (as no line check is required).

Arguments
infile		: const int file descriptor of file to read
outfile 	: const int file descriptor of file to write to.

*/
void print_all(const int infile, const int outfile){
	int n = 0;
	char buffer[BUFFERSIZE];

	//read() returns the number of byte read
   	while((n = read(infile, buffer, BUFFERSIZE)) > 0){
     	write(outfile, buffer, n);
   }
}  



/*
Given infile and outfile, this function copy the infile to the outfile. c struct
object contains the neccessary information to perform the copy operation. File that
are copied can be performed in 2 different ways: 
1) To print to outfile
2) To print to stdout (outfile == 1).

Arguments
infile	: file descriptor of the file to be copied.
outfile	: file descriptor for the file to be copied to.
c		: char source		: source path of the file to be copied.
		  char destination	: destination path for the file to be copied to.
		  int limit			: number of lines to be copied.
		  bool tail			: true indicate tail mode else head.

Return 	: Exit status, if write fails return 2 (exit status), if read fails return
		  1 as exit status, else return 0.

*/
int copy_file(int *infile, int *outfile, Copy c){
	char *successMsg;
	
	// open infile for copy
	if (!open_read_file(infile, c.source)){
		return 1;		// error code 1
	}
	
	// If destination is specified write to destination.
	if(c.destination != NULL) {
		if(!open_write_file(outfile, c.destination)){
			return 2;	// error code 2
		}
		successMsg = "Copy successful\n";
	}else{
		// if outfile == 1: print/copy to stdout, hence, dont need to open write_file.
		// print nothing when write to terminal
		successMsg = ""; 
	}
	// write to file/ terminal
	// check if copy in tail mode
	if(c.tail){
		tail(*infile, *outfile, c.limit);
	}else{
		head(*infile, *outfile, c.limit);
	}
	
	// print success Message if copied successfully.
	write(1, successMsg, strlen(successMsg));
	return 0;
}
