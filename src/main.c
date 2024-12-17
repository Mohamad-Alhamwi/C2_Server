# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define PORT 8888 // The port users will be connecting to.

int createSocket();
int setSocketOptions(int listening_socket_fd);
int bindSocketToIp(int listening_socket_fd, const struct sockaddr * server_address, socklen_t address_length);
int listenForConnections(int listening_socket_fd, int connections_length);
int acceptConnections(int listening_socket_fd, struct sockaddr * restrict client_address, socklen_t * restrict address_length);
ssize_t sendResponse(int communicating_socket_fd, const void * response_message, size_t message_length, int flags);
ssize_t receiveClientData(int communicating_socket_fd, void * buffer, size_t length, int flags);
void closeSocket(int socket_fd);
void throwError(const char * custom_err_msg);

int main(void)
{
    errno = 0;         // Initialize errno to indicate no errors initially.
    int listening_socket_fd;     // Listen on listening_socket_fd.
    int communicating_socket_fd;
    int socket_options; 
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(struct sockaddr_in);
    ssize_t client_data_length = 0;
    char received_data_buffer [1024];

    /* Set up a TCP/IP socket */
    listening_socket_fd = createSocket();

    if(listening_socket_fd == -1)
    {
        throwError("Failed to create a socket");
    }

    /* Set socket options. */
    socket_options = setSocketOptions(listening_socket_fd);

    if(socket_options == -1)
    {
        throwError("Failed to set socket options.");
    }

    /* Set the server's address realted variables. */
    server_address.sin_family = AF_INET;         // Address family.
    server_address.sin_port = htons(PORT);       // Short, network byte order.
    server_address.sin_addr.s_addr = 0;          // filled with the servers’s current IP address.
    memset(&(server_address.sin_zero), '\0', 8); // Zero the rest of the struct.
    
    int bind_status = bindSocketToIp(listening_socket_fd, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    
    if(bind_status == -1)
    {
        throwError("Failed to bind socket to ip.");
    }

    int connections_length = 5;

    int listening_status = listenForConnections(listening_socket_fd, connections_length);
    
    if(listening_status == -1)
    {
        throwError("Failed to listen.");
    }

    /* Print server listening information */
    printf("Server is listening on ip: %s, port: %d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));

    // Accept loop.
    while (1)
    {
        communicating_socket_fd = acceptConnections(listening_socket_fd, (struct sockaddr *) &client_address, &client_address_length);
        
        if(communicating_socket_fd == -1)
        {
            throwError("Failed to accept incoming connections.");
        }

        printf("Server: got connection from %s port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        ssize_t bytes_sent = sendResponse(communicating_socket_fd, "Hello, world!\n", 13, 0);

        client_data_length = receiveClientData(communicating_socket_fd, received_data_buffer, 1024, 0);

        while(client_data_length > 0)
        {
            printf("Received: %d bytes\n", client_data_length);
            client_data_length = receiveClientData(communicating_socket_fd, received_data_buffer, 1024, 0);
        }

        close(communicating_socket_fd);
    }

    closeSocket(listening_socket_fd);

    return 0;
}

int createSocket()
{
    return socket(PF_INET, SOCK_STREAM, 0);
}

int setSocketOptions(int listening_socket_fd)
{
    int yes = 1;
    return setsockopt(listening_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}

int bindSocketToIp(int listening_socket_fd, const struct sockaddr * server_address, socklen_t address_length)
{
    return bind(listening_socket_fd, server_address, address_length);
}

int listenForConnections(int listening_socket_fd, int connections_length)
{
    return listen(listening_socket_fd, connections_length);
}

int acceptConnections(int listening_socket_fd, struct sockaddr * restrict client_address, socklen_t * restrict address_length)
{
    return accept(listening_socket_fd, client_address, address_length);
}

ssize_t sendResponse(int communicating_socket_fd, const void * response_message, size_t message_length, int flags)
{
    return send(communicating_socket_fd, response_message, message_length, flags);
}

ssize_t receiveClientData(int communicating_socket_fd, void * buffer, size_t length, int flags)
{
    return recv(communicating_socket_fd, &buffer, length, flags);
}

void closeSocket(int socket_fd)
{
    close(socket_fd);
    printf("Socket with FD %d closed successfully.\n", socket_fd);
}

void throwError(const char * custom_err_msg)
{
    fprintf(stderr, "%s.\n", custom_err_msg);
    fprintf(stderr, "Error Number: %d.\n", errno);
    fprintf(stderr, "Error Description: %s.\n", strerror(errno));
    fprintf(stderr, "Aborted.\n");
    exit(EXIT_FAILURE);
}
