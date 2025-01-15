# ifndef SERVER_HANDLER_H
# define SERVER_HANDLER_H

ssize_t receiveServerData(int sock_fd, const char *data_buff, size_t data_buff_size, int flags);
ssize_t sendDataToServer(int sock_fd, const void *msg, size_t msg_len, int flags);

# endif