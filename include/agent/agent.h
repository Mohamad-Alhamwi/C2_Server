# ifndef AGENT_H
# define AGENT_H

void startAgent(const char *server_ip, int server_port);
void closeAgent(int sock_fd);

# endif