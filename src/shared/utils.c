#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "shared/utils.h"

void abortOperation()
{
    fprintf(stderr, ERROR "[-] " RESET "Aborted.\n");
    fflush(stderr);  // Ensure the abort message is printed.
    exit(EXIT_FAILURE);
}

void throwError(const char *custom_err_msg, int should_abort)
{
    /*Handle errors that occur in a system call or library function.*/
    fprintf(stderr, ERROR "[-] " RESET "Server: (%d) %s.\n", errno, custom_err_msg);
    fflush(stderr);  // Ensure the error message is printed.
    fprintf(stderr, ERROR "[-] " RESET "Error Description: %s.\n", strerror(errno));
    fflush(stderr);  // Ensure error description is printed.

    if(should_abort != FALSE)
    {
        abortOperation();
    }

    // TODO: Handle custom errors.
    return;
}

void cleanUpResources(int cleanup_type, void *resource)
{
    switch(cleanup_type)
    {
        case CLEANUP_FILE_DESCRIPTORS:
            if (resource != NULL)
            {
                int *fd = (int *) resource; // Cast to int pointer.
                if (*fd >= 0)
                {
                    close(*fd);
                    printf("Closed file descriptor %d.\n", *fd);
                }
            }
            break;

        case CLEANUP_MEMORY:
            if (resource != NULL)
            {
                free(resource); // Free the dynamically allocated memory.
                printf("Freed allocated memory.\n");
            }
            break;

        default:
            throwError("Invalid cleanup type", FALSE);
            break;
    }

    return;
}

void getTime(char *buff, size_t buff_size)
{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    if(local_time == NULL)
    {
        snprintf(buff, buff_size, "Uknown Time");
        return;
    }

    // Format the time into the buffer.
    strftime(buff, buff_size, "%Y-%m-%d %H:%M:%S", local_time);
}

// TODO: Implement a log function.

// TODO: Handle buffer flushing in general.