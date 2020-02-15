CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g
TARGET = command_write_request.o command_read_request.o libcommand_write_request.so libcommand_read_request.so logger.o thread.o liblogger.so server.o command_stdin.o reactor.o fd_listener.o socket.o server.out
INCLUDE_DIRS = -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/ -I../factory/ -I../socket/ -I../project/reactor/


default: all

all: $(TARGET)

command_write_request.o: command_write_request.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

command_read_request.o: command_read_request.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

libcommand_write_request.so: command_write_request.o
	$(CC) $(CFLAGS) -shared $< -o $@

libcommand_read_request.so: command_read_request.o
	$(CC) $(CFLAGS) -shared $< -o $@

logger.o: ../logger/logger.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

thread.o: ../thread/thread.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

liblogger.so: thread.o logger.o
	$(CC) $(CFLAGS) thread.o logger.o -shared -o $@

server.o: server.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

command_stdin.o: command_stdin.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

reactor.o: ../project/reactor/reactor.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

fd_listener.o: ../project/reactor/fd_listener.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

socket.o: ../socket/socket.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

server.out: server_app.cpp server.o command_stdin.o reactor.o fd_listener.o socket.o
	$(CC) $(CFLAGS) -fPIC $< server.o command_stdin.o reactor.o fd_listener.o socket.o -pthread -lboost_system -Wl,-rpath,. -L. -llogger -ldl -rdynamic -o $@ $(INCLUDE_DIRS)

clean:
	-rm *.o

.PHONY: all

