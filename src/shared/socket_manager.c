# include "socket_manager.h"
# include "utils.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

int createSocket()
{
    return socket(PF_INET, SOCK_STREAM, 0);
}

int setSocketOptions(int listening_sock_fd)
{
    int yes = 1;
    return setsockopt(listening_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}

int bindSocketToIp(int listening_sock_fd, const struct sockaddr *server_addr, socklen_t addr_len)
{
    return bind(listening_sock_fd, server_addr, addr_len);
}

int listenForConnections(int listening_sock_fd, int connections_len)
{
    return listen(listening_sock_fd, connections_len);
}

int acceptConnections(int listening_sock_fd, struct sockaddr *restrict client_addr, socklen_t *restrict addr_len)
{
    return accept(listening_sock_fd, client_addr, addr_len);
}

void closeSocket(int sock_fd)
{
    cleanUpResources(CLEANUP_FILE_DESCRIPTORS, &sock_fd);
    return;
}
