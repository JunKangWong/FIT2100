/* task3.c: append the contents of the second file to the first file */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>      /* needed for perror function */
#include <string.h>

#define BUFFER_SIZE 1024

int main (int argc, char *argv[])
{
  int n, infile, outfile;
  char buffer[BUFFER_SIZE];
  

  if (argc != 3) { /* Q: what does argc (argument count) mean? */
      write(2, "Usage: ./appendfile file1 file2\n", 32);
      exit(1);
  }

  /*
  * Open the second file (file2) for reading
  */
  if ((infile = open(argv[2], O_RDONLY)) < 0) {
      perror(argv[2]);
      exit(1);
  }

  /*
  * CODE HERE: Open the first file (file1) for writing
  */
  if ((outfile = open(argv[1], O_WRONLY|O_APPEND, 0664)) < 0){
      perror(argv[1]);
      exit(1);
  }
  

  /*
  * CODE HERE: Copy data from the second file to the first file
  */
  //read() returns the number of byte read
   while((n = read(infile, buffer, BUFFER_SIZE)) > 0){
     write(outfile, buffer, n);
   }

  /* 
  * CODE HERE: Close files before exiting
  */
  close(infile);
  close(outfile);

  exit(0);
}



// Other approach

  /*
  /*
  while((byte_read = read(infile, buffer, BUFFER_SIZE) > 0)){

    // set the buffer of size to nto write whatever read into the buffer into outfile.
	lseek(outfile, n, SEEK_END);
	write(outfile, buffer, byte_read);

    n += byte_read;
   }
   */
   
   /*
   
  while((byte_read = read(infile, buffer, BUFFER_SIZE) > 0)){

    // set the buffer of size to nto write whatever read into the buffer into outfile.
	//lseek(outfile, sizeof(n), SEEK_END);
	write(outfile, buffer, byte_read);

    //n += byte_read;
   }

   */
