SOURCES = $(wildcard *.c)
OBJECTS = $(SRCS:.c=.o)
TESTS = $(SRCS:.c=.out)
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -Iinclude
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3
TARGET = dlist_test sorted_list_test priority_q_test scheduler_test

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.c, %.o, $(wildcard $(TDIR)/*_test.c))

default: all

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dlist_test: $(OBJECTS_DLIST)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(OBJECTS_DLIST) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

.PHONY: all