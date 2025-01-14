#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <sys/socket.h>
#include <netinet/in.h>

int createSocket();
int setSocketOptions(int listening_sock_fd);
int bindSocketToIp(int listening_sock_fd, const struct sockaddr *server_addr, socklen_t addr_len);
int listenForConnections(int listening_sock_fd, int connections_len);
int acceptConnections(int listening_sock_fd, struct sockaddr *restrict client_addr, socklen_t *restrict addr_len);
int connectToAddress(int sock_fd, const struct sockaddr *addr, socklen_t addr_len);
void closeSocket(int sock_fd);

#endif
