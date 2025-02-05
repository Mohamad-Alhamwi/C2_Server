#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/socket_manager.h"
#include "server/server.h"
#include "server/agent_handler.h"

void startServer(int port, int backlog)
{
    int listening_sock_fd;
    struct sockaddr_in server_addr;
    int sock_opts, is_bound, is_listening;
    Agent agent;
    ssize_t agent_data_length;
    char time_buff[TIMESTAMP_BUFFER_SIZE];

    /* Create and configure the server socket. */
    listening_sock_fd = createSocket();

    if(listening_sock_fd == -1)
    {
        throwError("Failed to create socket", NULL, TRUE);
    }

    /* Set socket options. */
    sock_opts = setSocketOptions(listening_sock_fd);

    if(sock_opts == -1)
    {
        closeServer(listening_sock_fd); // Clean up server resources.
        throwError("Failed to set socket options", NULL, TRUE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;        // Bind the server to all available IP addresses on the host.
    zeroBuffer(&(server_addr.sin_zero), '\0', 8);    // Zero the rest of the struct.

    is_bound = bindSocketToIp(listening_sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if(is_bound == -1)
    {
        closeServer(listening_sock_fd); // Clean up server resources.
        throwError("Failed to bind socket", NULL, TRUE);
    }

    is_listening = listenForConnections(listening_sock_fd, backlog);

    if(is_listening == -1)
    {
        closeServer(listening_sock_fd); // Clean up server resources.
        throwError("Failed to listen", NULL, TRUE);
    }

    getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);
    printf("\n" "[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Server is up and running on %s:%d\n\n", time_buff, inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    /* Listening while for accepting connections. */
    while(TRUE)
    {
        // Accept a new connection.
        agent.addr_len = sizeof(struct sockaddr_in);
        int agent_sock_fd = acceptConnections(listening_sock_fd, (struct sockaddr *) &agent.addr, &agent.addr_len);
        
        if(agent_sock_fd == -1)
        {   
            /* Log the error, skip the current iteration, and retry accepting connections. */
            throwError("Failed to accept connection", NULL, FALSE);
            continue;
        }

        // Initialize agent.
        initAgent(&agent, agent_sock_fd);

        // Send a message to the connected agent.
        ssize_t is_sent = sendDataToAgent(&agent, "Hello, world!\n", 14, 0);

        if(is_sent == -1)
        {   
            // TODO: Add a mechanism to resend data to agent. For now you are just killing the existing one
            // and proceeding to the next one. 
            throwError("Failed to send data to agent", NULL, FALSE);
            killAgent(&agent);
            continue;
        }

        /* Handling while for handling connections. */
        while(TRUE)
        {
            agent_data_length = receiveAgentMessage(&agent, 0);

            if(agent_data_length == -1)
            {
                // TODO: Add a mechanism to investigate the problem further. For now just kill the agent and move on.
                throwError("Error occurred while receiveing data from agent", NULL, FALSE);
                break;
            }

            if(agent_data_length == 0)
            {
                break;
            }
        }

        /* Close the agent connection after communication ends. */
        killAgent(&agent);
    }

    /* Close the server socket. */
    closeServer(listening_sock_fd);
    
    return;
}

void closeServer(int sock_fd)
{
    closeSocket(sock_fd);

    char time_buff[TIMESTAMP_BUFFER_SIZE];
    getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);

    printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Server has been shut down\n", time_buff);
    return;
}
