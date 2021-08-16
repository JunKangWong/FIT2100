/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void test_func();

// Quesrion how to write() integer without using function like itoa and string? -- Ask KH

struct Record {
  int unitid;
  char unitcode[8];
};


// define gloabal unitcodes array
char *unitcodes[] = {"FIT2100", "FIT1047", "FIT3159", "FIT3142"};


int main(int argc, char *argv[])
{
  int i, infile, oddfile, evenfile;
  struct Record eachrec;

  
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 1 pathname O_RDONLY (Read only).
  if ((infile = open("recordfile", O_RDONLY)) < 0) {
    exit(1);
  }
  
  if ((oddfile = open("odd", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
    exit(1);
  }
  
  if ((evenfile = open("even", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
    exit(1);
  }

	
  for (i = 1; i >=-2; i --){

    // The file offset is set to offset from the beginning of the file.
    // move file pointer to i * sizeof(struct Record) from the beginning.
    // read data based on their i position
    // ((n%M)+M%M) is used to simulate the mathematical behavior of modulus for negative numbers.
    // 1 --> 0 --> 3 --> 2
    lseek(infile, (long) ((i%4)+4)%4 * sizeof(struct Record), SEEK_SET);
    read(infile, &eachrec, sizeof(struct Record));
    
    // write Unit ID onto terminal
    write(1, eachrec.unitcode, strlen(eachrec.unitcode));
    write(1, "\n", 1);
    
    // write 
    if (eachrec.unitid % 2 == 1){ // odd
    	lseek(oddfile, (long) (eachrec.unitid-1)/2 * sizeof(eachrec.unitcode), SEEK_SET);
    	write(oddfile, &eachrec.unitcode, sizeof(eachrec.unitcode));
    	
    }else{ // even
    	lseek(evenfile, (long) eachrec.unitid/2 * sizeof(eachrec.unitcode), SEEK_SET);
    	write(evenfile, &eachrec.unitcode, sizeof(eachrec.unitcode));
    }
    
 }
  
  write(1, "\nTest\n", 6);
  test_func();
  // close file and terminates successfully. --> how to close all?
  close(infile);
  close(oddfile);
  close(evenfile);
  
  exit(0);
}


void test_func(){
  int i, oddfile, evenfile;
  struct Record odd;
  struct Record even;
  
  if ((oddfile = open("odd", O_RDONLY)) < 0) {
    exit(1);
  }
  
  if ((evenfile = open("even", O_RDONLY)) < 0) {
    exit(1);
  }
  
  for (i = 0; i <= 1; i ++){

    // The file offset is set to offset from the beginning of the file.
    // move file pointer to i * sizeof(struct Record) from the beginning.
    // read data based on their i position
    // ((n%M)+M%M) is used to simulate the mathematical behavior of modulus for negative numbers.
    // 1 --> 0 --> 3 --> 2
	  lseek(oddfile, (long) i * sizeof(odd.unitcode), SEEK_SET);
	  read(oddfile, &odd.unitcode, sizeof(odd.unitcode));
	  write(1, "odd", 3);
	  write(1, odd.unitcode, strlen(odd.unitcode));
	  write(1, "\n", 1),
	  
	  lseek(evenfile, (long) i * sizeof(even.unitcode), SEEK_SET);
	  read(evenfile, &even.unitcode, sizeof(even.unitcode));
	  write(1, "even", 4);
	  write(1, even.unitcode, strlen(even.unitcode));
	  write(1, "\n", 1);
	  
 }

} 


            
