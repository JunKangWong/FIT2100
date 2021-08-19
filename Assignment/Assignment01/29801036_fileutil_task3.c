/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);\

#include <stdio.h>
#include <stdbool.h>

/*Function prototype*/
//void read_file(char *source);
void open_read_file(int *infile, char *source);
void open_write_file(int *outfile, char *source);
char *concat_string(char *str1, char *str2);
bool is_valid_path(char *path, char *full_path);
bool is_valid_path2(char *path, char *filename);
void read_lines(int infile, int outfile, int line_cnt);
void read_all(int fd);



int main(int argc, char *argv[])
{
	int infile, outfile;
	int opt;
	
	//open_file(&infile, argv[1]);
	
	while((opt = getopt(argc, argv, "d:")) != -1)
	{
		switch(opt)
		{
			case 'd':
			{
			
				char *filename = "sample.txt";
				int fpath_len = strlen(optarg) + strlen(filename);
				char full_path[fpath_len];
				strcat(strcpy(full_path, optarg), filename);
				
				
				if (argc == 3){
					open_read_file(&infile, "sample.txt");
				}else if (argc == 4){
					open_read_file(&infile, argv[1]);
				}
				//if destination not exist / if destination has file with same name as source file.
				if (!is_valid_path(optarg, full_path)){
				
					char *errorMsg = "Invalid destination\n";
					write(2, errorMsg, strlen(errorMsg));
					close(infile);
					close(outfile);
					exit(2);
					
				}else{

					write(1, full_path, fpath_len);
					
					// opens file in destination optarg write mode
					open_write_file(&outfile, full_path);
					
					// read first 10 lines of inline into outfile
					read_lines(infile, outfile, NUM_OF_LINE);
				}
				break;
			}
			default:
				write(1, "DEFAULT", 7);
		}
	}
  



  
  /*
  
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
	*/
	

  
  // perform file based on the number of lines specified.
  //outfile = 1;
  //read_lines(infile, outfile, NUM_OF_LINE);
 
 
 
  // close file and terminates successfully.
  close(infile);
  close(outfile);
  exit(0);
  
  //return 0;
}



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
*/

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


bool is_valid_path(char *path, char *full_path){
	bool file_exist = (access(full_path, F_OK) == 0) ? true : false;
	
	// check if file path exists
	bool dir_exist = (access(path, F_OK) == 0) ? true : false;

	// return true if directory exists and file with same name doesnt exists.
	return (dir_exist && !file_exist);
}


/*
char *concat_string(char *str1, char *str2){

	int combined_len  = strlen(str1) + strlen(str2);
	char new_str[combined_len];
	strcat(strcpy(new_str, str1), str2);
	
	return new_str;
}
*/




// can combine with below func
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



/*
// This file reads the content from the file infile and output put the file into an outfile.
void read_and_write(int infile, int outfile){

	read_lines


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
	

      */
