#include <stdio.h>
#include <arpa/inet.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "agent/server_handler.h"

/* Receive data from server. */
ssize_t receiveServerData(int sock_fd, char *data_buff, size_t data_buff_size, int flags)
{
    char time_buff[TIMESTAMP_BUFFER_SIZE];
    ssize_t bytes_received = recv(sock_fd, data_buff, data_buff_size, flags);

    if (bytes_received > 0)
    {
        char *trimmed_str = trimTrailing(data_buff);
        getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);
        
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Received (%zd bytes) from the server\n", time_buff, bytes_received);
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Received from the server: %s\n", time_buff, trimmed_str);
    
        free(trimmed_str);
        trimmed_str = NULL;
    }

    return bytes_received;
}

/* Send response to server. */
ssize_t sendDataToServer(int sock_fd, const void *msg, size_t msg_len, int flags)
{
    return send(sock_fd, msg, msg_len, flags);
}