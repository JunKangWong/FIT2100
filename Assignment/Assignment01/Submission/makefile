OBJS = 29801036_fileutil.o 29801036_file_manipulations.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall


fileutil: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o fileutil


29801036_fileutil.o: 29801036_fileutil.c 29801036_fileutil.h
	$(CC) $(CFLAGS) 29801036_fileutil.c


29801036_file_manipulations.o: 29801036_file_manipulations.c 29801036_file_manipulations.h
	$(CC) $(CFLAGS) 29801036_file_manipulations.c
