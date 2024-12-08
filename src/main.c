# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define PORT 8888 // The port users will be connecting to.

int createSocket();
int setSocketOptions(int socket_fd);
void closeSocket(int socket_fd);
void throwError(const char * custom_err_msg);

int main(void)
{
    errno = 0;         // Initialize errno to indicate no errors initially.
    int socket_fd;     // Listen on socket_fd.
    int socket_opt; 
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    /* Set up a TCP/IP socket */
    socket_fd = createSocket();

    if(socket_fd == -1)
    {
        throwError("Failed to create a socket");
    }

    printf("Socket created successfully. FD: %d\n", socket_fd);

    /* Set socket options. */
    socket_opt = setSocketOptions(socket_fd);

    if(socket_opt == -1)
    {
        throwError("Failed to set socket options.");
    }

    printf("Socket options set successfully.\n");

    return 0;
}

int createSocket()
{
    return socket(PF_INET, SOCK_STREAM, 0);
}

int setSocketOptions(int socket_fd)
{
    int yes = 1;
    return setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
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
