# Compiler and flags.
CC = gcc
CFLAGS = -Wall -Iinclude

# Source files for server and agent.
SERVER_SRC = main_server.c src/server/server.c src/server/agent_handler.c src/shared/socket_manager.c src/shared/utils.c src/shared/time.c
AGENT_SRC = main_agent.c src/agent/agent.c src/agent/server_handler.c src/shared/socket_manager.c src/shared/utils.c src/shared/time.c

# Object files for server and agent.
SERVER_OBJ = $(SERVER_SRC:.c=.o)
AGENT_OBJ = $(AGENT_SRC:.c=.o)

# Executables.
SERVER_EXEC = server
AGENT_EXEC = agent

# Default target.
all: $(SERVER_EXEC) $(AGENT_EXEC)

# Build the server executable.
$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER_EXEC)

# Build the agent executable.
$(AGENT_EXEC): $(AGENT_OBJ)
	$(CC) $(CFLAGS) $(AGENT_OBJ) -o $(AGENT_EXEC)

# Compile each .c file into its corresponding .o file.
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

main_server.o: main_server.c
	$(CC) $(CFLAGS) -c $< -o $@

main_agent.o: main_agent.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files.
clean:
	rm -f $(SERVER_OBJ) $(AGENT_OBJ) main_server.o main_agent.o
