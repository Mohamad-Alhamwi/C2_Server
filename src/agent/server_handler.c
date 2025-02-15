#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/log_manager.h"
#include "agent/server_handler.h"

/* Receive data from server. */
ssize_t receiveServerData(int sock_fd, char *data_buff, size_t data_buff_size, int flags)
{
    ssize_t bytes_received = recv(sock_fd, data_buff, data_buff_size, flags);

    if (bytes_received > 0)
    {
        char *trimmed_str = trimTrailing(data_buff);

        logTerminal(LOG_SUCCESSFUL, "Received (%zd bytes)", bytes_received);
        logTerminal(LOG_SUCCESSFUL, "Received from the server: %s", trimmed_str);
    
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