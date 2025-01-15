
# include "agent/server_handler.h"
# include <stddef.h>

/* Receive data from server. */
ssize_t receiveServerData(int sock_fd, const char *data_buff, size_t data_buff_size, int flags)
{
    ssize_t bytes_received = recv(sock_fd, data_buff, sizeof(data_buff), flags);

    if (bytes_received > 0)
    {
        // TODO: Why type casting (int)bytes_received???
        printf("Received (%zd bytes) from %s:%d\n", bytes_received, inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port));
    }

    return bytes_received;
}

/* Send response to server. */
ssize_t sendDataToServer(int sock_fd, const void *msg, size_t msg_len, int flags)
{
    return send(sock_fd, msg, msg_len, flags);
}
