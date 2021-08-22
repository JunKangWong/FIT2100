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


int main(int argc, char **argv){
	int n_val = 0;
	int opt;
	bool opt_L = false, opt_d = false;
	char *source_path = NULL, *dest_path = NULL, *dest_dir = NULL;
	
	char *filename = "simple.txt"; // default file
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
		//source_path = (char *) realloc(source_path, strlen(argv[optind]) + 1);
		//strcpy(source_path, argv[optind]);
		store_str(&source_path, argv[optind], true);
	}
	
	// get destination address if applicable.
	printf("dest_dir: %s\nsource_path: %s\nbase: %s\n", dest_dir, source_path, basename(source_path));
	
	// if dest_dir is null meaning no -d option is selected.
	if(dest_dir != NULL) get_dest_path(dest_dir, basename(source_path), &dest_path);
	
	
	//printf("%s\n", argv[optind]);
	
	printf("%s\n%s\n", source_path, dest_path);
	
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
	return true;
}



/*

void process_options(int argc, char **argv){

}

*/




