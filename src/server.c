#include "server.h"
#include "socket_manager.h"
#include "client_handler.h"
#include "utils.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void startServer(int port)
{
    int listening_socket_fd, communicating_socket_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(struct sockaddr_in);
    char received_data_buffer[1024];
    ssize_t client_data_length;

    /* Create and configure the server socket */
    listening_socket_fd = createSocket();
    if (listening_socket_fd == -1)
        throwError("Failed to create a socket");

    if (setSocketOptions(listening_socket_fd) == -1)
        throwError("Failed to set socket options");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    if (bindSocketToIp(listening_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        throwError("Failed to bind socket");

    if (listenForConnections(listening_socket_fd, 5) == -1)
        throwError("Failed to listen");

    printf("Server is listening on port %d\n", port);

    /* Accept and handle connections */
    while (1)
    {
        communicating_socket_fd = acceptConnections(listening_socket_fd, (struct sockaddr *)&client_address, &client_address_length);
        if (communicating_socket_fd == -1)
            throwError("Failed to accept connection");

        printf("Got connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        sendResponse(communicating_socket_fd, "Hello, world!\n", 13, 0);
        while ((client_data_length = receiveClientData(communicating_socket_fd, received_data_buffer, 1024, 0)) > 0)
        {
            printf("Received: %zd bytes\n", client_data_length);
        }

        closeSocket(communicating_socket_fd);
    }

    closeSocket(listening_socket_fd);
}
