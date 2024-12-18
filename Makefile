CC = gcc
CFLAGS = -Wall -Iinclude
OBJ = src/socket_manager.c src/client_handler.c src/utils.c src/server.c main.c

all: server

server:
	$(CC) $(CFLAGS) $(OBJ) -o server

clean:
	rm -f server
