#include "29801036_file_manipulations.h"



/* File path manipulation functions */


/*

Given a string and a buffer this function Stores str (String) in to buffer.

Arguments

buffer		: a char pointer that is used to store dynamic (malloc) string.
str			: a char* string to be stored
reallocate	: a bool indicate the on/off of reallocate mode.
			  true indicates the buffer is already allocated hence use realloc 
			  instead of malloc.

*/
bool store_str(char **buffer, const char* str, const bool reallocate){

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
		
	}else{
		*path = (char *) malloc(strlen(dir) + strlen(filename) + 2);
		
		if (*path == NULL) {
		
			const char *errorMsg = "ERROR: Pointer is NULL after memory allocation.\n";
			write(2, errorMsg, strlen(errorMsg));
			
			return false;
		}
		
		strcpy(*path, dir);
		strcat(*path, "/");
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
Outfile	: 
Source	:

*/
bool open_write_file(int *outfile, const char *source){
	if ((*outfile = open(source, O_WRONLY | O_CREAT | O_EXCL , 0664)) < 0){
	
		if(errno == EEXIST){
		
			const char *errorMsg = "ERROR: File with the same name already exists.\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
			
		}else if(errno == ENOENT){
		
			const char *errorMsg = "ERROR: Destination directory does not exist.\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
		
		}else{ // other reaspns
		
			const char *errorMsg = "Failed to open write file\n";
			write(2, errorMsg, strlen(errorMsg));
			return false;
		}
	}

	return true;
}


/*
Given two arguments infile and source, this function reads file content in the
source path into infile.
*/
bool open_read_file(int *infile, const char *source){
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((*infile = open(source, O_RDONLY)) < 0) {
	  	if(errno == ENOENT){
	  	
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



void head(const int infile, const int outfile, const int limit){ 
	size_t lines = 0;
	char c;


	while(read(infile, &c, 1) > 0 && lines < limit){
	
		// write character by character to terminal
		write(outfile, &c, 1);
		
		// increment when encounter '\n'.
		if(c == '\n') lines ++;
	}
}



void tail(const int infile, const int outfile, const int limit){
	int i = -1, lines = 0;
	char c;
	

	while(lseek(infile, i * sizeof(char), SEEK_END) != -1 && lines <= limit){
		read(infile, &c, 1);
		
		if (c == '\n') lines ++;
		i--;
	}

	//write character by character to terminal
	lseek(infile, (long) i+2 * sizeof(char), SEEK_END);
	lseek(outfile, 0, SEEK_SET);
	head(infile, outfile, limit+1);
}



/*Explain the design rationale*/
int copy_file(int *infile, int *outfile, Copy c){

	// open infile for copy
	if (!open_read_file(infile, c.source)){
		return 1; 	// error code 1
	}
	
	// if outfile == 1: print/copy to stdout, hence, dont need to open write_file.
	if(c.destination != NULL) {
		if(!open_write_file(outfile, c.destination)){
			return 2; // error code 2
		}
	}
	
	// check if copy in tail mode
	if(c.tail){
		tail(*infile, *outfile, c.limit);
	}else{
		head(*infile, *outfile, c.limit);
	}
	
	if(c.destination != NULL) {
		char *successMsg = "Copy successful\n";
		write(1, successMsg, strlen(successMsg));
	}
	return 0;
}
