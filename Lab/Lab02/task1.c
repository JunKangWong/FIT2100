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

char *unitcodes[] = {"FIT2100", "FIT1047", "FIT3159", "FIT3142"};

int main(int argc, char *argv[])
{
  int i, outfile;
  struct Record eachrec;

  if ((outfile = open("recordfile", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) {
    exit(1);
  }

  for (i = 3; i >= 0; i -=2) {
    eachrec.unitid = i;
    strcpy(eachrec.unitcode, unitcodes[i]);

    lseek(outfile, (long) i * sizeof(struct Record), SEEK_SET);
    write(outfile, &eachrec, sizeof(struct Record));

    if (i == 1) {
      i = 4;
    }
  }

  close(outfile);
  exit(0);
}