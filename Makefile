CC = gcc
CFLAGS = -Wall -Iinclude
OBJ = src/agent_handler.c src/server.c src/socket_manager.c src/utils.c main.c

all: server

server:
	$(CC) $(CFLAGS) $(OBJ) -o server

clean:
	rm -f server
