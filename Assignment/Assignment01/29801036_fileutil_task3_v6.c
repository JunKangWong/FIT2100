/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME 255
#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);


#include <stdio.h>
#include <stdbool.h>
#include <libgen.h>

/*Function prototype*/
//void read_file(char *source);
void open_read_file(int *infile, char *source);
void open_write_file(int *outfile, char *source);
char *concat_string(char *str1, char *str2);
bool is_valid_path(char *full_path);
void open_and_write_file(int *infile, int *outfile, char *insource, char *outsource, int line_cnt); // put param in a struct ltr
void read_lines(int infile, int outfile, int line_cnt);
void read_all(int fd);

// filename manipulations
void get_copy_path(char *from_path, char *dest_dir, char *new_path);
void get_filename(char *from_path, char *filename);



/*
free();

include a section in doc to talk about how i makesure i quits cleanly

write assumption in docs for backslash

change char to const char if possible

validate number of arg applicable

*/
	


int main(int argc, char *argv[])
{
	// absolute paths
	char from_path[BUFFERSIZE], dest_path[BUFFERSIZE];
	int infile, outfile;
	int opt;
	int n_val = NUM_OF_LINE;
	bool opt_d = false;

		getcwd(from_path, sizeof(from_path));
		strcat(from_path, "/sample.txt");
	/*
	if (argc == 1){
		// initialise default from_path to local sample.txt file
		getcwd(from_path, sizeof(from_path));
		strcat(from_path, "/sample.txt");
	}else if (argc == 2){
		// if exactly 2 arguments specified
		getcwd(from_path, sizeof(from_path));
		strcat(from_path, argv[1]);
	}
	*/

	while((opt = getopt(argc, argv, "d:n:")) != -1)
	{
		switch(opt)
		{	// Task 3 - copy file
			case 'd':
			{
				opt_d = true;
				
				if (strcmp(argv[1], "-d") != 0){
					strcpy(from_path, argv[1]);
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
				n_val = atoi(optarg);
				break;
			}case '?':
			{
				// print error Msg
				break;
			}default:
			{
			
			}
		}
	}
	
	
	if (opt_d){
		// exits if dest path is not absolute path
		if (dest_path[0] != '/'){
			const char *errorMsg = "ERROR: destination path is not absolute\n";
			write(2, errorMsg, strlen(errorMsg));
			exit(1);
		}
		// open infile from from path and outfile from dest_path then 
		// copy content of infile to outfile (default 10 lines);
		open_and_write_file(&infile, &outfile, from_path, dest_path, n_val);

		// print success msg if copied successfully.
		char *successMsg = "Copy successful\n";
		write(1, successMsg, strlen(successMsg));
		
	}else{
		open_read_file(&infile, from_path);
		read_lines(infile, 1, n_val);
	}

  
  //perform file based on the number of lines specified.
  //outfile = 1;
  //read_lines(infile, outfile, NUM_OF_LINE);
 
 

  // close file and terminates successfully.
  close(infile);
  close(outfile);
  exit(0);
  
  //return 0;
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
}



bool is_valid_path(char *full_path){
	// check if file already exists
	bool file_exist = (access(full_path, F_OK) == 0) ? true : false;
	
	// check if file path exists
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



/*Given a file descriptor this function reads all content of the file*/
void read_all(int fd){
	int n = 0;
	char buffer[BUFFERSIZE];

	//read() returns the number of byte read
   	while((n = read(fd, buffer, BUFFERSIZE)) > 0){
     	write(1, buffer, n);
   }
}




/*File path manipulation functions*/
void get_copy_path(char *from_path, char *dest_dir, char *new_path){
	char *this_path = strdup(from_path);
	strcpy(new_path, dest_dir);
	strcat(new_path, basename(from_path));
}



void get_filename(char *path, char *filename){
	char *p = strrchr(path, '/');
	strcpy(filename, ++p);
}




/*
// This file reads the content from the file infile and output put the file into an outfile.
void read_and_write(int infile, int outfile){

	read_lines
*/




/*
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

	

      */
