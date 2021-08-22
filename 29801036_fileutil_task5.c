/* task4.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);


#include <stdio.h> 
#include <stdbool.h>
#include <libgen.h>

typedef struct{
	char *source;
	char *destination;
	int line_cnt;
	int reverse; // use as bool
}Copy;



/*Function prototype*/
void open_read_file(int *infile, char *source);
void open_write_file(int *outfile, char *source);
bool is_valid_path(char *full_path); // change name to is valid write path
//void open_and_write_file(int *infile, int *outfile, char *insource, char *outsource, int line_cnt); // put param in a struct ltr
void copy_file(int *infile, int *outfile, Copy c);
void read_lines(int infile, int outfile, int line_cnt);
void tail(int infile, int outfile, int line_cnt);
void get_copy_path(char *from_path, char *dest_dir, char *new_path);



/*
free(); --> needed?

- include a section in doc to talk about how i makesure i quits cleanly
- write assumption in docs for backslash
- write assumption for file path length
- change char to const char if possible
- validate number of arg applicable

// 1) put param in a struct ltr for open and write;
		- explain why we use struct --> too many variables
		- ordering of the variables causes unwanted dependency
		- only keep immutable details in struct
		- 	Good practice only 
// 2) Allow reverse mode for read and --> affects open and write
// 3) change name to is valid write path from is valid path
// 4) Change open and write file --> copy file
// rmb to remove stdio.h

add support for '/'
- use strrchr to look for "/" and p ++ to see if its "\0" 

	5) change some int to size_t
	6) rename readlines --> head

// confirm set error no with kah hee does that mean "exit(2);"

*/





int main(int argc, char *argv[])
{
	// absolute paths
	char from_path[BUFFERSIZE], dest_path[BUFFERSIZE];
	int infile, outfile;
	int opt;
	int n_val = NUM_OF_LINE;
	int opt_d = 0, opt_n = 0, opt_L = 0;



	/*Arguments check*/
	// check if source file is provided
	if (argc > 1 && access(argv[1], F_OK) == 0){
		strcpy(from_path, argv[1]);
	
	// check if argv[1] is an option if yes --> use default sample.txt file
	}else if (argc == 1 || (argc > 1 && argv[1][0] == '-')){
		// initialise default from_path to local sample.txt file
		getcwd(from_path, sizeof(from_path));
		strcat(from_path, "/sample.txt");
		
	}else{
		const char *errorMsg1 = "ERROR: Source path don't exists or invalid arguments\n";
		write(2, errorMsg1, strlen(errorMsg1));
		exit(1);
	}


	/*Option Check*/
	while((opt = getopt(argc, argv, "d:n:L")) != -1)
	{
		switch(opt)
		{	// Task 3 - copy file
			case 'd':
			{
				opt_d += 1; // true
				
				// exits if dest dir is not absolute path
				if (optarg[0] != '/'){
					const char *errorMsg2 = "ERROR: destination path is not absolute\n";
					write(2, errorMsg2, strlen(errorMsg2));
					exit(1);
				}
				/* 
				load necessary information into buffer;
				given "from_path" (path to copy from) and destination directory:
				generate destination path into dest_path variable.
				*/
				get_copy_path(from_path, optarg, dest_path);
				break;
			}case 'n':
			{	
				opt_n += 1;
				n_val = atoi(optarg);
				break;
			}case 'L':
			{
				opt_L += 1;
				break;
			}default:
			{
				exit(1);
			}
		}
	}
	
	// check if any repeated option is used
	if (opt_d > 1 || opt_n > 1 || opt_L > 1){
		const char *errorMsg3 = "ERROR: Each option can only be used once\n";
		write(2, errorMsg3, strlen(errorMsg3));
		exit(1);
	}
	
	/*Action based on options*/
	if (opt_d){

		Copy metadata;

		metadata.source = from_path;
		metadata.destination = dest_path;
		metadata.line_cnt = n_val;
		metadata.reverse = opt_L;
		
		// open infile from from path and outfile from dest_path then 
		// copy content of infile to outfile (default 10 lines);
		copy_file(&infile, &outfile, metadata);
	}else{
		open_read_file(&infile, from_path);
		read_lines(infile, 1, n_val);
	}

  // close file and terminates successfully.
  close(infile);
  close(outfile);
  exit(0);
  
  //return 0;
}



void copy_file(int *infile, int *outfile, Copy c){
	if (!is_valid_path(c.destination)){
		char *errorMsg = "Invalid write destination\n";
		write(2, errorMsg, strlen(errorMsg));
		exit(2);
	}

	open_read_file(infile, c.source);
	open_write_file(outfile, c.destination);
	read_lines(*infile, *outfile, c.line_cnt);
	
	// print success msg if copied successfully.
	char *successMsg = "Copy successful\n";
	write(1, successMsg, strlen(successMsg));
}



bool is_valid_path(char *full_path){
	// check if file already exists at the path
	bool file_exist = (access(full_path, F_OK) == 0) ? true : false;
	
	// check if file directory exists
	char *dup_fpath = strdup(full_path);
	bool dir_exist = (access(dirname(dup_fpath), F_OK) == 0) ? true : false;

	// return true if directory exists and file with same name doesnt exists.
	return (dir_exist && !file_exist);
}


/*
Given two arguments infile and source, this function opens the file in write mode
and if the file doesn't already exist create a new file, or if the file is not empty
truncate it.
*/
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



/*
Given the file descriptor(fd) and line count (line_cnt)
This function reads
*/
void read_lines(int infile, int outfile, int line_cnt){
	size_t lines = 0;
	char c;
	
	while(read(infile, &c, 1) > 0 && lines < line_cnt){
	
		// write character by character to terminal
		write(outfile, &c, 1);
		
		// increment when encounter '\n'.
		if(c == '\n') lines ++;
		
	}
	
}

/*
Referenced from:
https://www.geeksforgeeks.org/implement-your-own-tail-read-last-n-lines-of-a-huge-file/

*/
void tail(int infile, int outfile, int line_cnt){
	int cnt = 0;
	size_t pos;
	char str[BUFFERSIZE];
	
	
	lseek(infile, 0, SEEK_END);
	lseek()

	// locate end of file
	if (fseek(in, 0, SEEK_END) < 0){
		close(infile);
		close(outfile);
		exit(1);
	}
}


/*File path manipulation functions*/
void get_copy_path(char *from_path, char *dest_dir, char *new_path){
	char *this_path = strdup(from_path);
	strcpy(new_path, dest_dir);
	strcat(new_path, basename(from_path));
}












/*

// This file reads the content from the file infile and output put the file into an outfile.
void read_and_write(int infile, int outfile){

	read_lines

Check if the given path is valid and whether it is an absolute path
if it does not fufil either condition  exits and return error code 2.

bool is_valid_path(char *path, char *full_path){
	//int fpath_len = strlen(path) + strlen(filename);
	//char full_path[fpath_len];

	// check if the file with the same filename already exist
	strcat(strcpy(full_path, path), full_path);
	bool file_exist = (access(full_path, F_OK) == 0) ? true : false;
	
	// check if file path exists
	bool dir_exist = (access(path, F_OK) == 0) ? true : false;

	// return true if directory exists and file with same name doesnt exists.
	return (dir_exist && !file_exist);
}


bool is_valid_path2(char *path, char *filename){
	int fpath_len = strlen(path) + strlen(filename);
	char full_path[fpath_len];

	// check if the file with the same filename already exist
	strcat(strcpy(full_path, path), filename);
	bool file_exist = (access(filename, F_OK) == 0) ? true : false;
	
	// check if file path exists
	bool dir_exist = (access(path, F_OK) == 0) ? true : false;

	// return true if directory exists and file with same name doesnt exists.
	return (dir_exist && !file_exist);
}


}

bool is_absolute_path(){}



				int test = strcmp(optarg, "") == 0 ? 1 : 0;
				printf("Equivalent? %d\n", test);
				
// check if file path is absolute
	bool is_absolute = (strcmp(path[0] ,"/") == 0) true ? false;


	
	
	// can check access(path, F_OK) + access() == 0 --> something along the line
	
	// if directory doesn't exists or file with same name already exists output 
	// error message and exits
	if(!dir_exist || file_exist){
		char *outString = "Directory doesnt exists or file with the same name already exists\n";
		write(2, outString, strlen(outString));
		exits(2); // exit like this is not clean
	}
	
	
	void open_and_write_file(int *infile, int *outfile, char *insource, char *outsource, char *dest_dir){
	
	if (!is_valid_write_path(outsource)){
		char *errorMsg = "Invalid write destination\n";
		write(2, errorMsg, strlen(errorMsg));
		exit(2);
	}

	open_read_file(&infile, insource);
	open_write_file(&outfile, outsource);
	read_lines(infile, outfile, NUM_OF_LINE);
}



// File path manipulation functions
void get_copy_path(char *from_path, char *dest_dir, char *new_path){
	char *p = strrchr(from_path, '/');
	strcpy(new_path, dest_dir);
	strcat(new_path, ++p); // dangerous
}

//Given a file descriptor this function reads all content of the file
void read_all(int fd){
	int n = 0;
	char buffer[BUFFERSIZE];

	//read() returns the number of byte read
   	while((n = read(fd, buffer, BUFFERSIZE)) > 0){
     	write(1, buffer, n);
   }
}

void open_and_write_file(int *infile, int *outfile, char *insource, char *outsource, int line_cnt){
	if (!is_valid_path(outsource)){
		char *errorMsg = "Invalid write destination\n";
		write(2, errorMsg, strlen(errorMsg));
		exit(2);
	}

	open_read_file(infile, insource);
	open_write_file(outfile, outsource);
	read_lines(*infile, *outfile, line_cnt);
	
	// print success msg if copied successfully.
	char *successMsg = "Copy successful\n";
	write(1, successMsg, strlen(successMsg));
}

case '?':
			{
				const char *errorMsg = "Unknown Option\n";
				write(2, errorMsg, strlen(errorMsg));
				exit(1);
				break;
				
			}

*/
