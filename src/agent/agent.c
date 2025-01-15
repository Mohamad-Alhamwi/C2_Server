# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <arpa/inet.h>

# include "shared/utils.h"
# include "shared/socket_manager.h"
# include "agent/agent.h"
# include "agent/server_handler.h"

void startAgent(const char *server_ip, int server_port) 
{
    int sock_fd;
    char time_buff[DATE_TIME_BUFFER_SIZE];
    char server_data_buff[DATA_BUFFER_SIZE];
    ssize_t server_data_length;

    /* Create the agent socket. */
    sock_fd = createSocket();

    if (sock_fd == -1)
    {
        throwError("Failed to create socket.", TRUE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);            /* Host to network short. */
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr); /* Converts an IPv4 address from its text (human-readable) format to its numeric (binary) form. */

    int is_connected = connectToAddress(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if(is_connected == -1) 
    {
        closeAgent(sock_fd); // Clean up agent resources.
        throwError("Failed to connect to the server.", TRUE);
    }

    getTime(time_buff, sizeof(time_buff));
    printf("\n" SUCCESSFUL "[+] [%s] " RESET "Connected to server at %s:%d\n", time_buff, server_ip, server_port);

    server_data_length = receiveServerData(sock_fd, server_data_buff, sizeof(server_data_buff), 0);

    while (server_data_length > 0)
    {
        server_data_length = receiveServerData(sock_fd, server_data_buff, sizeof(server_data_buff), 0);
    }

        //server_data_buff[server_data_length] = '\0';  // Null-terminate the received data.
        printf("Received command: %s\n", server_data_buff);

        char result[1024] = "Command executed successfully.";
        // Simulate command execution and response.
        send(sock_fd, result, strlen(result), 0);

    //TODO: logic is not completed here.
}
