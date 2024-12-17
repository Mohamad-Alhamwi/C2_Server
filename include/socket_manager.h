#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <sys/socket.h>
#include <netinet/in.h>

int createSocket();
int setSocketOptions(int listening_socket_fd);
int bindSocketToIp(int listening_socket_fd, const struct sockaddr *server_address, socklen_t address_length);
int listenForConnections(int listening_socket_fd, int connections_length);
int acceptConnections(int listening_socket_fd, struct sockaddr *restrict client_address, socklen_t *restrict address_length);
void closeSocket(int socket_fd);

#endif
