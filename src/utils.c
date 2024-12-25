# include "utils.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define CLEANUP_FILE_DESCRIPTORS 1
# define CLEANUP_MEMORY  2

void abortOperation()
{
    fprintf(stderr, "Aborted.\n");
    fflush(stderr);  // Ensure the abort message is printed.
    exit(EXIT_FAILURE);
}

void throwError(const char *custom_err_msg, int should_abort)
{
    /*Handle errors that occur in a system call or library function.*/
    fprintf(stderr, "%s.\n", custom_err_msg);
    fflush(stderr);  // Ensure the custom error message is printed.
    fprintf(stderr, "Error Number: %d.\n", errno);
    fflush(stderr);  // Ensure error number is printed.
    fprintf(stderr, "Error Description: %s.\n", strerror(errno));
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
    switch (cleanup_type)
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

// TODO: Implement a log function.