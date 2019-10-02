IDIR = ./include
TDIR = ./test
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(IDIR)
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3
TARGET = dlist_test sorted_list_test priority_q_test scheduler_test

OBJECTS_DLIST = dlist.o ./test/dlist_test.o ./test/verify_funcs.o
OBJECTS_SORTED = dlist.o sorted_list.o ./test/sorted_list_test.o ./test/verify_funcs.o
OBJECTS_PQUEUE = dlist.o sorted_list.o priority_q.o ./test/priority_q_test.o ./test/verify_funcs.o
OBJECTS_SCHED = dlist.o sorted_list.o priority_q.o scheduler.o task.o uid.o ./test/scheduler_test.o ./test/verify_funcs.o


OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.c, %.o, $(wildcard $(TDIR)/*_test.c))

default: all

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dlist_test: $(OBJECTS_DLIST)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(OBJECTS_DLIST) -o $@

sorted_list_test: $(OBJECTS_SORTED)
	$(CC) $(CFLAGS) $(OBJECTS_SORTED) -o $@

priority_q_test: $(OBJECTS_PQUEUE)
	$(CC) $(CFLAGS) $(OBJECTS_PQUEUE) -o $@

scheduler_test: $(OBJECTS_SCHED)
	$(CC) $(CFLAGS) $(OBJECTS_SCHED) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

.PHONY: all