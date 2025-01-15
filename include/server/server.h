#ifndef SERVER_H
#define SERVER_H

void startServer(int port, int backlog);
void closeServer(int sock_fd);

#endif
