#include <stdio.h>
#include <arpa/inet.h>

#include "shared/utils.h"
#include "agent/server_handler.h"

/* Receive data from server. */
ssize_t receiveServerData(int sock_fd, char *data_buff, size_t data_buff_size, int flags)
{
    char time_buff[DATE_TIME_BUFFER_SIZE];
    ssize_t bytes_received = recv(sock_fd, data_buff, data_buff_size, flags);

    if (bytes_received > 0)
    {
        getTime(time_buff, sizeof(time_buff));
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Received (%zd bytes) from the server\n", time_buff, bytes_received);
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Received from the server: %s\n", time_buff, data_buff);
    }

    return bytes_received;
}

/* Send response to server. */
ssize_t sendDataToServer(int sock_fd, const void *msg, size_t msg_len, int flags)
{
    return send(sock_fd, msg, msg_len, flags);
}