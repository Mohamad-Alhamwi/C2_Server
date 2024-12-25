#include "server.h"

int main(void)
{
    int backlog = 5; // The maximum length to which the queue of pending connections may grow.
    int port = 8888;

    startServer(port, backlog);
    // TODO: check for invalid port numbers.
    // TODO: take backlog and port number information from CLI.
    return 0;
}
