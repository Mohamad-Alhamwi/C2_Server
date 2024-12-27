# include <stdio.h>
# include <stdlib.h>
# include "server.h"
# include "utils.h"

int main(int argc, char *argv[])
{
    int port = 8888; // Default port.
    int backlog = 5; // Default backlog.

    // Parse command-line arguments for port and backlog.
    if(argc == 1)
    {
        printf(INFORMATIONAL "[*] Starting server with default values:\n" RESET);
        printf(INFORMATIONAL "\t[*] Port: %d.\n\t[*] Backlog: %d.\n\n" RESET, port, backlog);
        printf(INFORMATIONAL "[*] Usage: %s <PORT> <BACKLOG>\n" RESET, argv[0]);
        printf(INFORMATIONAL "\t[*] <PORT>: The port on which the server will be listening for incoming connections.\n" RESET);
        printf(INFORMATIONAL "\t[*] <BACKLOG>: The maximum length to which the queue of pending connections may grow.\n\n" RESET);
    }

    if(argc >= 2)
    {
        port = atoi(argv[1]);  // Convert first argument to integer (port).

        if(port <= 0 || port > 65535)
        {
            throwError("Invalid port number. Please provide a port number between 1 and 65535", TRUE);
        }
    }

    if(argc >= 3)
    {
        backlog = atoi(argv[2]);  // Convert second argument to integer (backlog).

        if(backlog <= 0)
        {
            throwError("Invalid backlog value. Please provide a positive integer", TRUE);
        }
    }

    // Start the server.
    startServer(port, backlog);

    return 0;
}
