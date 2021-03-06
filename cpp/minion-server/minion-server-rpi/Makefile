CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g
TARGET = command_write_request.o command_read_request.o libcommand_write_request.so libcommand_read_request.so logger.o thread.o liblogger.so server.o command_stdin.o reactor.o fd_listener.o socket.o server.out
INCLUDE_DIRS = -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/ -I../factory/ -I../socket/ -I../reactor/
INCLUDE_BOOST = -I/boost_1_67_0 -L/boost_1_67_0/stage/lib

default: all

all: $(TARGET)

command_write_request.o: command_write_request.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

command_read_request.o: command_read_request.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

libcommand_write_request.so: command_write_request.o
	$(CC) $(CFLAGS) -shared $< -o $@

libcommand_read_request.so: command_read_request.o
	$(CC) $(CFLAGS) -shared $< -o $@

logger.o: ../logger/logger.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

thread.o: ../thread/thread.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

liblogger.so: thread.o logger.o
	$(CC) $(CFLAGS) thread.o logger.o -shared -o $@

server.o: server.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

command_stdin.o: command_stdin.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

reactor.o: ../reactor/reactor.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

fd_listener.o: ../reactor/fd_listener.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

socket.o: ../socket/socket.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

server.out: server_app.cpp server.o command_stdin.o reactor.o fd_listener.o socket.o
	$(CC) $(CFLAGS) -fPIC $< server.o command_stdin.o reactor.o fd_listener.o socket.o -pthread -lboost_system -Wl,-rpath,. -L. -llogger -ldl -rdynamic -o $@ $(INCLUDE_DIRS) $(INCLUDE_BOOST)

clean:
	-rm *.o

.PHONY: all
