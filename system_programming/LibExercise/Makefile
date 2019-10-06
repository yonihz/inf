CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3
TARGET = main.o a.o a1.o a2.o so1.o so2.o libar.a libso1.so libso2.so prog
OBJECTS_STATIC = a.o a1.o a2.o

default: all

all: $(TARGET)

main.o: main.c
	$(CC) -c -fPIC $< -o $@

a.o: a.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

a1.o: a1.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

a2.o: a2.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

so1.o: so1.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

so2.o: so2.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@	

libar.a: $(OBJECTS_STATIC)
	ar rcs $@ $(OBJECTS_STATIC)

libso1.so: so1.o
	$(CC) -shared $< -o $@

libso2.so: so2.o
	$(CC) -shared $< -o $@ main.o -L. -lar

prog: main.o libar.a so1.o so2.o
	gcc main.o -Wl,-rpath,. -lso1 -L. -lar -ldl -o $@

clean:
	-rm -f $(TARGET)

.PHONY: all