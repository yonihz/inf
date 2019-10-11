SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TESTS := $(SRCS:.c=.out)
EXCLUDE_FILES := task.out
TESTS := $(filter-out $(EXCLUDE_FILES),$(TESTS))
LIB := ./lib/libds.so

SRC_DIR := ./
OBJ_DIR := ./obj/
INC_DIR := ./include/
TEST_DIR := ./test/

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INC_DIR)
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3

OBJS1 := $(addprefix $(OBJ_DIR),$(OBJS))
TESTS1 := $(TESTS:.out=_test.out)

default: all

all: $(OBJS1) $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(LIB) : $(OBJS1)
	$(CC) -shared $^ -o $@

%_test.out : $(TEST_DIR)%_test.c $(SRCS)
	-$(CC) $(CFLAGS) $^ -o $@

.PHONY : debug
debug : CFLAGS += $(DEBUGFLAGS)
debug : all

.PHONY : release
release : CFLAGS += $(RELEASEFLAGS)
release : all

.PHONY : test
test : debug
test : $(TESTS1) 

.PHONY : clean
clean :
	rm -f $(OBJS1)
	rm -f $(LIB)
	rm -f $(TESTS1)

.PHONY: all