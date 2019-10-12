SRC_DIR := .
OBJ_DIR := ./obj
INC_DIR := ./include
TEST_DIR := ./test

SRCS := $(wildcard *.c)
SRCS_TEST := $(wildcard $(TEST_DIR)/*.c)
SRCS_TEST := $(SRCS_TEST:$(TEST_DIR)/%=%)
OBJS := $(SRCS:.c=.o)
OBJS_TEST := $(SRCS_TEST:.c=.o)
BINS_TESTS := $(SRCS_TEST:.c=.out)
LIB_RELEASE := ./lib/libds.so
LIB_DEBUG := ./lib/libds_debug.so

COMPILE = 
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INC_DIR)
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3
LDFLAGS = -shared

OBJS1 := $(addprefix $(OBJ_DIR)/,$(OBJS))
OBJS_TEST1 := $(addprefix $(OBJ_DIR)/,$(OBJS_TEST))

default: release

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(COMPILE) -fPIC -c $< -o $@

$(LIB_RELEASE) : $(OBJS1)
	$(CC) $(LDFLAGS) $^ -o $@

$(LIB_DEBUG) : $(OBJS1)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(TEST_DIR)/%.c
	$(CC) $(COMPILE) -fPIC -c $< -o $@

%.out : $(OBJ_DIR)/%.o $(LIB_DEBUG)
	$(CC) $< -Wl,-rpath,./lib -L./lib -lds_debug -o $@

.PHONY : debug
debug : COMPILE = $(CFLAGS) $(DEBUGFLAGS)
debug : $(LIB_DEBUG) $(OBJS1)

.PHONY : release
release : COMPILE = $(CFLAGS) $(RELEASEFLAGS)
release : $(LIB_RELEASE) $(OBJS1)

.PHONY: all
all: debug release

.PHONY : test
test : debug
test : COMPILE = $(CFLAGS) $(DEBUGFLAGS)
test : $(BINS_TESTS) $(OBJS_TEST1)

.PHONY : clean_obj
clean_obj :
	rm -f $(OBJS1)

.PHONY : clean
clean :
	rm -f $(OBJS1)
	rm -f $(OBJS_TEST1)
	rm -f $(LIB_RELEASE)
	rm -f $(LIB_DEBUG)
	rm -f $(BINS_TESTS)

#TODO: make all - do release, delete objects, debug and recreate objects 
#TODO: make test - not sure if to include both wl,rpath and L. 