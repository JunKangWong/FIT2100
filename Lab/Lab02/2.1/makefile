OBJS = main.o arithmetic.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall


arithmetic: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o arithmetic


main.o: main.c arithmetic.h
	$(CC) $(CFLAGS) main.c


arithmetic.o: arithmetic.c arithmetic.h
	$(CC) $(CFLAGS) arithmetic.c
