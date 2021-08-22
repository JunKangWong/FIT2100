#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libgen.h>

#include <stdio.h>  // testing only

#define BUFFERSIZE 1024		// used for read_all function only
#define NUM_OF_LINE 10  	// set default head() as head(10);


typedef struct{
	char *source;
	char *destination;
	int line_cnt;
	int reverse; // use as bool
}Copy;


bool get_dest_path(char *dest_dir, char *filename, char **dest_path);
bool store_str(char **buffer, char* str, bool reallocate);

void open_write_file(int *outfile, char *source);
void open_read_file(int *infile, char *source);

void head(int infile, int outfile, int line_cnt);
void tail(int infile, int outfile, int limit);

bool is_valid_write_path(char *full_path);
void copy_file(int *infile, int *outfile, Copy c);



int main(int argc, char **argv){
	Copy c;
	int infile, outfile; 
	int n_val = NUM_OF_LINE;		// number of lines to write to 10 by default.
	int opt;
	bool opt_L = false, opt_d = false;

	// malloc pointers
	char *source_path = NULL, *dest_path = NULL, *dest_dir = NULL;
	
	char *filename = "sample.txt"; // default file
	store_str(&source_path, filename, false);
	
	
		/*Option Check*/
	while((opt = getopt(argc, argv, "d:n:L")) != -1)
	{
		switch(opt)
		{	// Task 3 - copy file
			case 'd':
			{
				store_str(&dest_dir, optarg, false);
				break;
			}case 'n':
			{	
				n_val = atoi(optarg);
				break;
			}case 'L':
			{
				opt_L = true;
				break;
			}
		}
	}

	// replace new source address if user key in.
	if (optind + 1 <= argc){
		store_str(&source_path, argv[optind], true);
	}

	// if dest_dir is null meaning no -d option is selected.
	if(dest_dir != NULL) {
		get_dest_path(dest_dir, basename(source_path), &dest_path);
	}else{
		outfile = 1;
	}

	
	//printf("dest_dir: %s\nsource_path: %s\nbase: %s\n", dest_dir, source_path, basename(source_path));
	

	// create inistalise the Copy object and pass into copy file function together with infile and outfile
	c.source = source_path;
	c.destination = dest_path;
	c.line_cnt = n_val;
	c.reverse = opt_L;
	
	// perform copy file operations.
	copy_file(&infile, &outfile, c);
	
	// free all dynamic arrays in the heap
	free(source_path);
	free(dest_path);
	free(dest_dir);
	
	// close all files
	close(infile);
	close(outfile);
	
	// exits program
	exit(0);

}


// store str into buffer
bool store_str(char **buffer, char* str, bool reallocate){

	if(reallocate){
		*buffer = (char *) realloc(*buffer, strlen(str) + 1);
	}else{
		*buffer = (char *) malloc(strlen(str) + 1);
	}

	if (*buffer == NULL) return false; // exit?
	strcpy(*buffer, str);
	
	return true;
}



/*File path manipulation functions*/
bool get_dest_path(char *dest_dir, char *filename, char **dest_path){
	// Check if last character of destination path is '/' if not add manually.
	char last_c = dest_dir[strlen(dest_dir)-1];
	char first_c = dest_dir[0];
	
	// directory is not absolute
	if (first_c != '/') return false;
	
	if (last_c == '/'){
		*dest_path = (char *) malloc(strlen(dest_dir) + strlen(filename) + 1);
		
		if (*dest_path == NULL) return false;
		strcpy(*dest_path, dest_dir);
		strcat(*dest_path, filename);
	}else{
		*dest_path = (char *) malloc(strlen(dest_dir) + strlen(filename) + 2);
		if (*dest_path == NULL) return false;
		
		strcpy(*dest_path, dest_dir);
		strcat(*dest_path, "/");
		strcat(*dest_path, filename);
	}
	
	return is_valid_write_path(*dest_path);
}



bool is_valid_write_path(char *full_path){
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
  	printf("FAILED: %s\n", source);
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
		read(infile, &c, 1);
		
		if (c == '\n') lines ++;
		i--;
	}
	
	//write character by character to terminal
	lseek(infile, (long) (++i) * sizeof(char), SEEK_END);
	head(infile, outfile, limit+1);
}




void copy_file(int *infile, int *outfile, Copy c){
	// open infile for copy
	open_read_file(infile, c.source);
	
	// if outfile == 1: print/copy to stdout, hence, dont need to open write_file.
	if(c.destination != NULL) open_write_file(outfile, c.destination);

	// check if copy in reverse 
	if(c.reverse){
		tail(*infile, *outfile, c.line_cnt);
	}else{
		head(*infile, *outfile, c.line_cnt);
	}

	// print success msg if copied successfully.
	char *successMsg = (c.destination != NULL) ? "Copy successful\n" : "";
	write(1, successMsg, strlen(successMsg));
}







/*

void process_options(int argc, char **argv){

}

	
	// get destination address if applicable.
	//printf("dest_dir: %s\nsource_path: %s\nbase: %s\n", dest_dir, source_path, basename(source_path));
	
	
*/




