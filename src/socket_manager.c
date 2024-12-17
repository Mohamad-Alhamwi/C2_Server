#include "socket_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int createSocket()
{
    return socket(PF_INET, SOCK_STREAM, 0);
}

int setSocketOptions(int listening_socket_fd)
{
    int yes = 1;
    return setsockopt(listening_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}

int bindSocketToIp(int listening_socket_fd, const struct sockaddr *server_address, socklen_t address_length)
{
    return bind(listening_socket_fd, server_address, address_length);
}

int listenForConnections(int listening_socket_fd, int connections_length)
{
    return listen(listening_socket_fd, connections_length);
}

int acceptConnections(int listening_socket_fd, struct sockaddr *restrict client_address, socklen_t *restrict address_length)
{
    return accept(listening_socket_fd, client_address, address_length);
}

void closeSocket(int socket_fd)
{
    close(socket_fd);
    printf("Socket with FD %d closed successfully.\n", socket_fd);
}
