#include "client_handler.h"
#include <sys/socket.h>

ssize_t sendResponse(int communicating_socket_fd, const void *response_message, size_t message_length, int flags)
{
    return send(communicating_socket_fd, response_message, message_length, flags);
}

ssize_t receiveClientData(int communicating_socket_fd, void *buffer, size_t length, int flags)
{
    return recv(communicating_socket_fd, buffer, length, flags);
}