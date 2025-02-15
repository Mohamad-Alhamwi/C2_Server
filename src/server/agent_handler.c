#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/log_manager.h"
#include "shared/socket_manager.h"
#include "server/agent_handler.h"

/* Initialize a new agent structure. */
void initAgent(Agent *agent, int sock_fd)
{
    agent -> sock_fd = sock_fd;
    initializeBuffer(agent -> data_buff, 0, sizeof(agent -> data_buff));
}

/* Receive data from agent. */
ssize_t receiveAgentMessage(Agent *agent, int flags)
{
    ssize_t bytes_received = recv(agent -> sock_fd, agent -> data_buff, sizeof(agent -> data_buff), flags);

    if (bytes_received > 0)
    {
        char *trimmed_str = trimTrailing(agent->data_buff);

        logTerminal(LOG_SUCCESSFUL, "[%s:%d] Received (%zd bytes)", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), bytes_received);
        logTerminal(LOG_SUCCESSFUL, "[%s:%d] Received: %s", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port), trimmed_str);

        free(trimmed_str);
        trimmed_str = NULL;
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

    logTerminal(LOG_INFORMATIONAL, "Closed connection with %s:%d", inet_ntoa(agent -> addr.sin_addr), ntohs(agent -> addr.sin_port));

    return;
}
