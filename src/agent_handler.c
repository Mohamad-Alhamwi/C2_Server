# include "utils.h"
# include "agent_handler.h"
# include "socket_manager.h"
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <arpa/inet.h>

/* Initialize a new agent structure. */
void initAgent(Agent *agent, int sock_fd)
{
    agent -> sock_fd = sock_fd;
    // TODO: implement a function for clearing.
    memset(agent -> data_buff, 0, sizeof(agent -> data_buff));  // Clear the buffer.
}

/* Receive data from agent. */
ssize_t receiveAgentData(Agent *agent, int flags)
{
    ssize_t bytes_received = recv(agent -> sock_fd, agent -> data_buff, sizeof(agent -> data_buff), flags);

    if (bytes_received > 0)
    {
        printf("Received from %s:%d: %.*s\n", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), (int)bytes_received, agent -> data_buff);
    }

    return bytes_received;
}

/* Send response to agent. */
ssize_t sendDataToAgent(Agent *agent, const void *msg, size_t msg_len, int flags)
{
    return send(agent -> sock_fd, msg, msg_len, flags);
}

/* Close agent connection. */
void closeAgent(Agent *agent)
{
    closeSocket(agent -> sock_fd);
    printf("Closed connection with %s:%d\n", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port));
}
