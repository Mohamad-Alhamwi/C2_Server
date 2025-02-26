#ifndef AGENT_HANDLER_H
#define AGENT_HANDLER_H

#include <sys/types.h>
#include <netinet/in.h>

#include "shared/message_manager.h"

/* Define the Agent structure */
typedef struct
{
    int sock_fd;                      // Agent's socket file descriptor.
    struct sockaddr_in addr;          // Agent's address (IP, port).
    socklen_t addr_len;               // Agent's address length.
    char data_buff [MSG_BUFF_SIZE];            // Buffer for communication.
} Agent;

/* Agent handler functions */
void initAgent(Agent *agent, int sock_fd);
ssize_t receiveAgentMessage(Agent *agent, int flags);
ssize_t sendDataToAgent(Agent *agent, const void *msg, size_t msg_len, int flags);
void killAgent(Agent *agent);

#endif