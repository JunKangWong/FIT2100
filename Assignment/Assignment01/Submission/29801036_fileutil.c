/*
Name			: Wong Jun Kang
Student ID		: 29801036
Date created	: 19/08/2021
Last modified	: 24/08/2021

The c module contains the main logic of fileutil. This module include all the memory
allocation handling (free()) and ensures that file are closed before exiting the program
(ensure exits  cleanly.)
*/

#include "29801036_fileutil.h"


/*
Main function of fileutil

argc	: argument count input by user in terminal.
argv	: list of arguments input by user in terminal.

return 	: int 0, indicate successful completion of fileutil
*/
int main(int argc, char **argv){
	Copy metadata;
	int infile, outfile; 
	int n_val = NUM_OF_LINE;		// number of lines to write to 10 by default.
	int opt;
	bool opt_L = false;
	int exit_status = 0;

	// malloc pointers
	char *source_path = NULL, *dest_path = NULL, *dest_dir = NULL;
	
	// sample file to use if user do not specify source file.
	const char *filename = "sample.txt"; // default file
	if(!store_str(&source_path, filename, false)) exit(1);
	
	// disabled default message from getopt and self define the error msg.
	opterr = 0; 
	
	/*Option Check*/
	while((opt = getopt(argc, argv, "d:n:L")) != -1)
	{
		switch(opt)
		{	// Task 3 - copy file
			case 'd':
			{
				// if there is error with dynamic array allocation or if path is not absolute 
				// free allocated memory and exits.
				if(!store_str(&dest_dir, optarg, false) || !(is_absolute_path(optarg))){	
					// free allocated malloc pointers and quits with errno 1.
					free(source_path);
					exit(1);
				}
				
				break;
			}case 'n':
			{	
				n_val = atoi(optarg);
				break;
			}case 'L':
			{
				opt_L = true;
				break;
			}case '?':
			{
				// prompt invalid arguments and then
				// free all allocated malloc pointers and exits.
				prompt_invalid_arguments(optopt);
				free(source_path);
				free(dest_dir);
				
				exit(1);
			}
		}
	}

	// replace new source address if user key in.
	// assume that source file will be first non option argument
	// ignores other non option input beside source file.
	if (optind < argc){
		if(!store_str(&source_path, argv[optind], true)){
			
			// free allocated malloc pointers and quits with errno 1
			free(source_path);
			free(dest_dir);
			
			exit(1);
		}
	}
	

	// if dest_dir is null meaning no -d option is selected.
	if(dest_dir != NULL) {
	
		// check if destination path is absolute (input format check)
		// check if dest_path is generated successfully.
		if(!get_path(dest_dir, basename(source_path), &dest_path)){
			
			// free allocated malloc pointers and quits with errno 1
			free(source_path);
			free(dest_dir);
			
			exit(1);
		}
	}else{
		// print to stdout if no destination path is specified.
		outfile = 1;
	}

	// create inistalise the Copy object and pass into copy file function together with infile and outfile
	metadata.source = source_path;
	metadata.destination = dest_path;
	metadata.limit = n_val;
	metadata.tail = opt_L;
	
	// perform copy file operations and retrive exit status.
	exit_status = copy_file(&infile, &outfile, metadata);
	
	// free all dynamic arrays in the heap
	free(source_path);
	free(dest_path);
	free(dest_dir);
	
	// close all files
	close(infile);
	close(outfile);
	
	// exits program
	exit(exit_status);
	
	return 0;
}


/* 
Parse Argument Check Functions
When the argument format/ input is invalid, this function checks for the reason 
of failure and output an appropriate error message to stderror accordingly.

opt	: int the option that error arise from.

 */
void prompt_invalid_arguments(int opt){
	switch(optopt)
	{
		case 'd':
		{
			const char *errorMsg = "Invalid argument: immediately after -d, a directory path was expected\n";
			write(2, errorMsg, strlen(errorMsg));
			break;
		}case 'n':
		{
			const char *errorMsg = "Invalid argument: no line numbers specified after the -n argument!\n";
			write(2, errorMsg, strlen(errorMsg));
			break;
		}default:{
			const char *errorMsg = "Unknown option!\n";
			write(2, errorMsg, strlen(errorMsg));
			break;
			
		}
	}
}

/*
This function checks if the input path is absolute

path	: const char* that specify the path to be checked.

Return	: bool true if the path is absolute else return false. 
*/
bool is_absolute_path(const char *path){
	if (path[0]!= '/'){
		const char *errorMsg = "Invalid argument: immediately after -d, a directory path was expected\n";
		write(2, errorMsg, strlen(errorMsg));
		return false;
	}
	return true;
}










