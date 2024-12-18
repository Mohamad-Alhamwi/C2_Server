#include "agent_handler.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/* Initialize a new agent structure. */
void initAgent(Agent *agent, int sock_fd, struct sockaddr_in *addr);
{
    agent -> agent_sock_fd = sock_fd;
    agent -> agent_addr = *addr;
    memset(agent -> agent_data_buff, 0, sizeof(agent -> agent_data_buff));  // Clear the buffer.
}

/* Receive data from agent. */
ssize_t receiveAgentData(Agent *agent, int flags);
{
    ssize_t bytes_received = recv(agent -> agent_sock_fd, agent -> agent_data_buff, sizeof(agent -> agent_data_buff), flags);

    if (bytes_received > 0)
    {
        printf("Received from %s:%d: %.*s\n", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), (int)bytes_received, agent -> agent_data_buff);
    }
    return bytes_received;
}

/* Send response to agent. */
ssize_t sendAgentData(Agent *agent, const void *msg, size_t msg_len, int flags);
{
    return send(agent -> agent_sock_fd, msg, msg_len, flags);
}

/* Close agent connection. */
void closeAgent(Agent *agent)
{
    close(agent -> agent_sock_fd);
    printf("Closed connection with %s:%d\n", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port));
}
