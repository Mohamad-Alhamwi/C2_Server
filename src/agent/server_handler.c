#include <stdio.h>
#include <arpa/inet.h>

#include "agent/server_handler.h"

/* Receive data from server. */
ssize_t receiveServerData(int sock_fd, char *data_buff, size_t data_buff_size, int flags)
{
    ssize_t bytes_received = recv(sock_fd, data_buff, sizeof(data_buff), flags);

    if (bytes_received > 0)
    {
        printf("Received (%zd bytes) from server\n", bytes_received);
    }

    return bytes_received;
}

/* Send response to server. */
ssize_t sendDataToServer(int sock_fd, const void *msg, size_t msg_len, int flags)
{
    return send(sock_fd, msg, msg_len, flags);
}
