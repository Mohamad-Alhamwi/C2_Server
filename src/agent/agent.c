#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/socket_manager.h"
#include "shared/buffer_manager.h"
#include "agent/agent.h"
#include "agent/server_handler.h"

void startAgent(const char *server_ip, int server_port) 
{
    int sock_fd;
    char time_buff[TIMESTAMP_BUFFER_SIZE];
    char server_data_buff[MSG_BUFF_SIZE];
    ssize_t server_data_length;

    /* Create the agent socket. */
    sock_fd = createSocket();

    if (sock_fd == -1)
    {
        throwError("Failed to create socket", NULL, TRUE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);            /* Host to network short. */
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    int is_connected = connectToAddress(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if(is_connected == -1) 
    {
        closeAgent(sock_fd); // Clean up agent resources.
        throwError("Failed to connect to the server", NULL, TRUE);
    }

    getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);
    printf("\n" "[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Connected to server at %s:%d\n\n", time_buff, server_ip, server_port);

    initializeBuffer(server_data_buff, 0, sizeof(server_data_buff));

     /* Handling while for handling communication with server. */
    while(TRUE)
    {
        server_data_length = receiveServerData(sock_fd, server_data_buff, sizeof(server_data_buff), 0);
        
        if(server_data_length == -1)
        {
            // TODO: Add a mechanism to investigate the problem further. For now just kill the agent.
            closeAgent(sock_fd);
            throwError("Error occurred while receiveing data from the server", NULL, TRUE);
        }

        /* Loop exits gracefully. */
        if(server_data_length == 0)
        {
            getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);
            printf("\n" "[" INFORMATIONAL "%s" RESET "] " "[" INFORMATIONAL "*" RESET "] " "Server closed the connection\n", time_buff);
            break;
        }

        // Send a message back to the server after processing.
        ssize_t is_sent = sendDataToServer(sock_fd, "Command executed successfully\n", 31, 0);

        if(is_sent == -1)
        {
            closeAgent(sock_fd);
            throwError("Failed to send data to server", NULL, TRUE);
        }
    }

    closeAgent(sock_fd);
}

void closeAgent(int sock_fd)
{
    closeSocket(sock_fd);

    char time_buff[TIMESTAMP_BUFFER_SIZE];
    getTimestamp(time_buff, FORMAT_FULL_TIMESTAMP);
    
    printf("[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Agent has been terminated\n", time_buff);
    
    return;
}