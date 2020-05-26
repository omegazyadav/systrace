CC=gcc
CFLAGS=-O -Wall

all: systrace

systrace: systrace.c
	$(CC) $(CFLAGS) -o $@ systrace.c $(LFLAGS)

clean: 
	rm systrace
