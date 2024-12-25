#include "server.h"
#include "socket_manager.h"
#include "agent_handler.h"
#include "utils.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void startServer(int port)
{
    int listening_sock_fd;
    struct sockaddr_in server_addr;
    int sock_opts, is_bound, is_listening;
    int backlog = 5; // The maximum length to which the queue of pending connections for listening_sock_fd may grow.
    Agent agent;
    ssize_t agent_data_length;

    /* Create and configure the server socket. */
    listening_sock_fd = createSocket();

    if(listening_sock_fd == -1)
    {
        throwError("Failed to create a socket.", TRUE);
    }

    /* Set socket options. */
    sock_opts = setSocketOptions(listening_sock_fd);

    if(sock_opts == -1)
    {
        closeServer(int sock_fd); // Clean up server resources.
        throwError("Failed to set socket options.", TRUE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;    // Bind the server to all available IP addresses on the host.
    memset(&(server_addr.sin_zero), '\0', 8);    // Zero the rest of the struct.

    is_bound = bindSocketToIp(listening_sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (is_bound == -1)
    {
        closeServer(int sock_fd); // Clean up server resources.
        throwError("Failed to bind socket.", TRUE);
    }

    is_listening = listenForConnections(listening_sock_fd, backlog);

    if (is_listening == -1)
    {
        closeServer(int sock_fd); // Clean up server resources.
        throwError("Failed to listen.", TRUE);
    }

    printf("Server is listening on port %d\n", port);

    /* Accept and handle connections. */
    while (1)
    {
        // Accept a new connection.
        agent.addr_len = sizeof(struct sockaddr_in);
        int new_sock_fd = acceptConnections(listening_sock_fd, (struct sockaddr *) &agent.addr, &agent.addr_len);
        
        if (new_sock_fd == -1)
        {   
            /*Log the error, skip the current iteration, and retry accepting connections.*/
            throwError("Failed to accept connection.", FALSE);
            continue;
        }

        // Initialize agent.
        initAgent(&agent, new_sock_fd);

        // Send a message to the connected agent.
        // TODO: Add a check for sendDataToAgent().
        sendDataToAgent(&agent, "Hello, world!\n", 13, 0);

        agent_data_length = receiveAgentData(&agent, 0);

        while (agent_data_length > 0)
        {
            printf("Received: %zd bytes\n", agent_data_length);
            agent_data_length = receiveAgentData(&agent, 0);
        }

        /* Close the agent connection after communication ends. */
        closeAgent(&agent);
    }

    /* Close the server socket. */
    closeServer(int sock_fd);
    
    return;
}

void closeServer(int sock_fd)
{
    void closeSocket(sock_fd);
    printf("Server has been shut down.\n");
    return;
}