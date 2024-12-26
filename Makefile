# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Source files and object files
SRC = src/agent_handler.c src/server.c src/socket_manager.c src/utils.c main.c
OBJ = src/agent_handler.o src/server.o src/socket_manager.o src/utils.o main.o

# Default target
all: server

# Build the server executable
server: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o server
	@rm -f $(OBJ) # Remove all .o files after linking

# Compile each .c file into its corresponding .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f server $(OBJ)
