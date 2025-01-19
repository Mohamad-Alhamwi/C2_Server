#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "shared/utils.h"
#include "shared/socket_manager.h"
#include "server/agent_handler.h"

/* Initialize a new agent structure. */
void initAgent(Agent *agent, int sock_fd)
{
    agent -> sock_fd = sock_fd;
    initializeBuffer(agent -> data_buff, 0, sizeof(agent -> data_buff));
}

/* Receive data from agent. */
ssize_t receiveAgentData(Agent *agent, int flags)
{
    char time_buff[DATE_TIME_BUFFER_SIZE];
    ssize_t bytes_received = recv(agent -> sock_fd, agent -> data_buff, sizeof(agent -> data_buff), flags);

    if (bytes_received > 0)
    {
        getTime(time_buff, sizeof(time_buff));
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "[%s:%d ----> Server]" " Received (%zd bytes)\n", time_buff, inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), bytes_received);
        printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Received from %s:%d: %s\n", time_buff, inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), trimTrailing(agent -> data_buff));
    }

    return bytes_received;
}

/* Send response to agent. */
ssize_t sendDataToAgent(Agent *agent, const void *msg, size_t msg_len, int flags)
{
    return send(agent -> sock_fd, msg, msg_len, flags);
}

/* Close agent connection. */
void killAgent(Agent *agent)
{
    closeSocket(agent -> sock_fd);

    char time_buff[DATE_TIME_BUFFER_SIZE];
    getTime(time_buff, sizeof(time_buff));
    printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Closed connection with %s:%d\n\n", time_buff, inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port));

    return;
}
