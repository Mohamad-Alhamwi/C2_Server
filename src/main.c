# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define PORT 8888 // The port users will be connecting to.

int createSocket();
int setSocketOptions(int socket_fd);
int bindSocketToIp(int socket_fd, const struct sockaddr * server_address, socklen_t address_length);
int listenForConnections(int socket_fd, int connections_length);
void closeSocket(int socket_fd);
void throwError(const char * custom_err_msg);

int main(void)
{
    errno = 0;         // Initialize errno to indicate no errors initially.
    int socket_fd;     // Listen on socket_fd.
    int socket_options; 
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    /* Set up a TCP/IP socket */
    socket_fd = createSocket();

    if(socket_fd == -1)
    {
        throwError("Failed to create a socket");
    }

    /* Set socket options. */
    socket_options = setSocketOptions(socket_fd);

    if(socket_options == -1)
    {
        throwError("Failed to set socket options.");
    }

    /* Set the server's address realted variables. */
    server_address.sin_family = AF_INET;         // Address family.
    server_address.sin_port = htons(PORT);       // Short, network byte order.
    server_address.sin_addr.s_addr = 0;          // filled with the servers’s current IP address.
    memset(&(server_address.sin_zero), '\0', 8); // Zero the rest of the struct.
    
    int bind_status = bindSocketToIp(socket_fd, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    
    if(bind_status == -1)
    {
        throwError("Failed to bind socket to ip.");
    }

    int connections_length = 5;

    int listening_status = listenForConnections(socket_fd, connections_length);
    
    if(listening_status == -1)
    {
        throwError("Failed to listen.");
    }

    closeSocket(socket_fd);

    return 0;
}

int createSocket()
{
    return socket(PF_INET, SOCK_STREAM, 0);
}

int setSocketOptions(int socket_fd)
{
    int yes = 1;
    return setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}

int bindSocketToIp(int socket_fd, const struct sockaddr * server_address, socklen_t address_length)
{
    return bind(socket_fd, server_address, address_length);
}

int listenForConnections(int socket_fd, int connections_length)
{
    return listen(socket_fd, connections_length);
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
