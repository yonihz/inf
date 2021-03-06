CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g
TARGET = command_write_request.o command_read_request.o libcommand_write_request.so libcommand_read_request.so logger.o thread.o liblogger.so server.o command.o command_console.o reactor.o fd_listener.o dir_monitor.o plugin_loader.o logger_configurator.o socket.o server.out
INCLUDE_DIRS = -I../minion-server/ -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/ -I../factory/ -I../socket/ -I../reactor/ -I../dir_monitor/ -I../dispatcher/


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

command.o: command.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

command_console.o: command_console.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

reactor.o: ../reactor/reactor.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

fd_listener.o: ../reactor/fd_listener.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

dir_monitor.o: ../dir_monitor/dir_monitor.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

plugin_loader.o: plugin_loader.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

logger_configurator.o: logger_configurator.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

socket.o: ../socket/socket.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ $(INCLUDE_DIRS)

server.out: server_app.cpp server.o command.o command_console.o reactor.o fd_listener.o dir_monitor.o plugin_loader.o logger_configurator.o socket.o
	$(CC) $(CFLAGS) -fPIC $< server.o command.o command_console.o reactor.o fd_listener.o dir_monitor.o plugin_loader.o logger_configurator.o socket.o -pthread -lboost_system -Wl,-rpath,. -L. -llogger -ldl -rdynamic -o $@ $(INCLUDE_DIRS)

clean:
	-rm *.o

clean_all:
	-rm *.o *.so *.out

.PHONY: all

