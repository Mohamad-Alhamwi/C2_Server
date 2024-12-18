# ifndef AGENT_HANDLER_H
# define AGENT_HANDLER_H

# include <netinet/in.h>
# include <sys/types.h>

/* Define the Agent structure */
typedef struct
{
    int agent_sock_fd;                      // Agent's socket file descriptor.
    struct sockaddr_in agent_addr;          // Agent's address (IP, port).
    char agent_data_buff [1024];            // Buffer for communication.
} Agent;

/* Agent handler functions */
void initAgent(Agent *agent, int sock_fd, struct sockaddr_in *addr);
ssize_t receiveAgentData(Agent *agent, int flags);
ssize_t sendAgentData(Agent *agent, const void *msg, size_t len, int flags);
void closeAgent(Agent *agent);

# endif