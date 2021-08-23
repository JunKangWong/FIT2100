#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libgen.h>
#include <errno.h>



typedef struct{
	char *source;
	char *destination;
	int limit;
	int tail; // use as bool
}Copy;


/*Function prototype*/
bool store_str(char **buffer, const char* str, const bool reallocate);

bool get_path(const char *dir, const char *filename, char **path);

bool open_write_file(int *outfile, const char *dest);

bool open_read_file(int *infile, const char *source);

void head(const int infile, const int outfile, const int limit);

void tail(const int infile, const int outfile, const int limit);

int copy_file(int *infile, int *outfile, Copy c);

