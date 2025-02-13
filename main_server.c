# include <stdio.h>
# include <stdlib.h>

# include "shared/utils.h"
# include "shared/buffer_manager.h"
# include "server/server.h"

void printUsageInformation(int port, int backlog, const char *program_name)
{
    printf("\n*************************************************************************************************\n");
    printf("* " INFORMATIONAL "[*] " RESET "Starting server with default values:\t\t\t\t\t\t\t*\n");
    printf("*        " INFORMATIONAL "[*] " RESET "Port: %d.\t\t\t\t\t\t\t\t\t*\n", port);
    printf("*        " INFORMATIONAL "[*] " RESET "Backlog: %d.\t\t\t\t\t\t\t\t\t*\n", backlog);
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t*\n");
    printf("* " INFORMATIONAL "[*] " RESET "Usage: %s <PORT> <BACKLOG>\t\t\t\t\t\t\t\t*\n", program_name);
    printf("*        " INFORMATIONAL "[*] " RESET "<PORT>: The port on which the server will be listening for incoming connections.\t*\n");
    printf("*        " INFORMATIONAL "[*] " RESET "<BACKLOG>: The maximum length to which the queue of pending connections may grow.\t*\n");
    printf("*************************************************************************************************\n");

    return;
}

int main(int argc, char *argv[])
{
    int port = 8888; // Default port.
    int backlog = 5; // Default backlog.

    // Parse command-line arguments for port and backlog.
    if(argc == 1)
    {
        printUsageInformation(port, backlog, argv[0]);
    }

    if(argc >= 2)
    {
        port = atoi(argv[1]);  // Convert first argument to integer (port).

        if(port <= 0 || port > 65535)
        {
            throwError("Invalid port number", "Please provide a port number between 1 and 65535", TRUE);
        }
    }

    if(argc >= 3)
    {
        backlog = atoi(argv[2]);  // Convert second argument to integer (backlog).

        if(backlog <= 0)
        {
            throwError("Invalid backlog value", "Please provide a positive integer", TRUE);
        }
    }

    // Start the server.
    startServer(port, backlog);

    return 0;
}
