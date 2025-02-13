# include <stdio.h>
# include <stdlib.h>

# include "shared/utils.h"
# include "shared/buffer_manager.h"
# include "agent/agent.h"

void printUsageInformation(const char *program_name)
{
    printf("\n*************************************************************************************************\n");
    printf("* " INFORMATIONAL "[*] " RESET "Usage: %s <PORT> <SERVER_ADDRESS>\t\t\t\t\t\t\t*\n", program_name);
    printf("*************************************************************************************************\n");

    return;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printUsageInformation(argv[0]);

        return 1;
    }

    /* TODO: Add parsing functionality for arguments. */
    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    startAgent(server_ip, server_port);

    return 0;
}
