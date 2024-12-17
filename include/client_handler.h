#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <sys/types.h>

ssize_t sendResponse(int communicating_socket_fd, const void *response_message, size_t message_length, int flags);
ssize_t receiveClientData(int communicating_socket_fd, void *buffer, size_t length, int flags);

#endif
