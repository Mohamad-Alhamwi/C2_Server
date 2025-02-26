#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/log_manager.h"

void abortOperation()
{
    logTerminal(LOG_ERROR, "Aborted");
    exit(EXIT_FAILURE);
}

void throwError(const char *custom_err_msg, const char *custom_err_description, int should_abort)
{
    /* Handle custom errors. */
    if (errno == 0)
    {
        logTerminal(LOG_ERROR, "Error (%d): %s", CUSTOM_ERR_NO, custom_err_msg);
        logTerminal(LOG_ERROR, "Description: %s", custom_err_description);
    }

    /* Handle system errors. */
    else  
    {
        logTerminal(LOG_ERROR, "Error (%d): %s", errno, custom_err_msg);
        logTerminal(LOG_ERROR, "Description: %s", strerror(errno));
    }

    /* Abort execution if needed. */
    if (should_abort)
    {
        abortOperation();
    }

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
                    logTerminal(LOG_INFORMATIONAL, "Closed file descriptor %d", *fd);
                }
            }
            break;

        case CLEANUP_MEMORY:
            if (resource != NULL)
            {
                free(resource); // Free the dynamically allocated memory.
                resource = NULL;
                printf("Freed allocated memory\n");
            }
            break;

        default:
            throwError("Failed to clean up resource", "Invalid cleanup type", FALSE);
            break;
    }

    return;
}

const char *trimLeading(const char *str)
{
    while (isspace((unsigned char) *str))
    {
        str++;
    }

    return str; // Return the pointer to the trimmed string.
}

char *trimTrailing(const char *str)
{
    // Make `end` point to the last element of the string.
    const char *end = str + strlen(str) - 1;

    // Move `end` backwards over trailing whitespace.
    while (end >= str && isspace((unsigned char) *end))
    {
        end--;
    }

    // Calculate the length of the trimmed string.
    size_t trimmed_length = (size_t) (end - str + 1);

    // Allocate memory for the trimmed string and account for the null-terminator.
    char *trimmed = malloc(trimmed_length + 1);
    if (!trimmed)
    {
        throwError("Failed to allocate memory", NULL, TRUE);
    }

    // Copy the trimmed string and null-terminate it.
    strncpy(trimmed, str, trimmed_length);
    trimmed[trimmed_length] = '\0';

     // Return the pointer to the trimmed string.
    return trimmed;
}

char *trimString(const char *str) 
{
    // Trim leading whitespace.
    const char *leading_trimmed = trimLeading(str);

    // Trim trailing whitespace.
    char *fully_trimmed = trimTrailing(leading_trimmed);

    return fully_trimmed;
}

void initializeBuffer(void * ptr, size_t buf_size)
{
    memset(ptr, '\0', buf_size);
    return;
}

// Define an alias for initializeBuffer().
void (*zeroBuffer)(void *, size_t) = initializeBuffer;