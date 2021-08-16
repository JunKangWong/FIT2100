/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


struct Record {
  int unitid;
  char unitcode[8];
};


// define gloabal unitcodes array
char *unitcodes[] = {"FIT2100", "FIT1047", "FIT3159", "FIT3142"};


int main(int argc, char *argv[])
{
  int i, outfile;
  struct Record eachrec;
  
  // int open(const char *pathname, int flags, mode_t mode);
  // mode_t --> permision of the file 0664 indicates -rw-rw-r--
  // open file in write mode, if the file doesn't exist, create it.
  // if the file descriptor of the file is less than 0 indicates an error hence exits.
  // Allows for 3 different pathname O_WRONLY (Write only). O_CREAT (create if doesnt exist),
  // O_TRUNC (file already exist) and is a regular file and access mode allows for write
  // truncate the length into 0 --> meaning clear the content of the file.
  if ((outfile = open("recordfile", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) {
    exit(1);
  }

  // loop from i = 3 --> 1 (--> 4 during if condition) --> 2 --> 0 (halts) 
  // and assign the unitid of eachrec with the corressponding corresponding i values.
  for (i = 3; i >= 0; i -=2) {
    // set unitid to current i.
    // for assign unit code at corressponding position i into eachrec.unitcode var.
    // In this sequence: 3 --> 1 --> 2 --> 0
    eachrec.unitid = i;
    strcpy(eachrec.unitcode, unitcodes[i]); 

    // The file offset is set to offset from the beginning of the file.
    // move file pointer to i * sizeof(struct Record) from the beginning.
    // write them side by side based on their i position (in order)
    // such that unitcode[0] and unitid = 0 will be placed as the first element in the file.
    // 0 --> 1 --> 2 --> 3 regardless of which element is put into the file first (3 __> 1 --> 2 --> 0).
    lseek(outfile, (long) i * sizeof(struct Record), SEEK_SET);
    write(outfile, &eachrec, sizeof(struct Record));

    if (i == 1) {
      i = 4;
    }   
  }

  // close file and terminates successfully.
  close(outfile);
  exit(0);
}

            
