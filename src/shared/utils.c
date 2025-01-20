#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "shared/time.h"
#include "shared/utils.h"

void abortOperation()
{
    char time_buff[DATE_TIME_BUFFER_SIZE];
    getTime(time_buff, FORMAT_FULL_DATETIME);

    fprintf(stderr, "[" INFORMATIONAL "%s" RESET "] " "[" ERROR "-" RESET "] " "Aborted\n", time_buff);
    fflush(stderr);  // Ensure the abort message is printed.
    exit(EXIT_FAILURE);
}

void throwError(const char *custom_err_msg, int should_abort)
{
    /* Handle errors that occur in a system call or library function .*/
    char time_buff[DATE_TIME_BUFFER_SIZE];
    getTime(time_buff, FORMAT_FULL_DATETIME);

    fprintf(stderr, "\n[" INFORMATIONAL "%s" RESET "] " "[" ERROR "-" RESET "] " "Server: (%d) %s\n", time_buff, errno, custom_err_msg);
    fflush(stderr);  // Ensure the error message is printed.
    fprintf(stderr, "[" INFORMATIONAL "%s" RESET "] " "[" ERROR "-" RESET "] " "Error Description: %s\n", time_buff, strerror(errno));
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
    char time_buff[DATE_TIME_BUFFER_SIZE];

    switch(cleanup_type)
    {
        case CLEANUP_FILE_DESCRIPTORS:
            if (resource != NULL)
            {
                int *fd = (int *) resource; // Cast to int pointer.

                if (*fd >= 0)
                {
                    close(*fd);
                    getTime(time_buff, FORMAT_FULL_DATETIME);
                    printf("\n" "[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] " "Closed file descriptor %d\n", time_buff, *fd);
                }
            }
            break;

        case CLEANUP_MEMORY:
            if (resource != NULL)
            {
                free(resource); // Free the dynamically allocated memory.
                // TODO: Nullify the pointer. (Use-after-free, Double free).
                printf("Freed allocated memory\n");
            }
            break;

        default:
            throwError("Invalid cleanup type", FALSE);
            break;
    }

    return;
}

void initializeBuffer(void * ptr, int value, size_t num)
{
    memset(ptr, value, num);
    return;
}

// Define an alias for initializeBuffer().
void (*zeroBuffer)(void *, int, size_t) = initializeBuffer;

const char *trimLeading(const char *str)
{
    /*
        *A function that trims leading whitespace by leveraging the built-in function isspace(), which checks for:
        *Space (' ').
        *Form feed ('\f').
        *Newline ('\n').
        *Carriage return ('\r').
        *Horizontal tab ('\t').
        *Vertical tab ('\v').
    */

    while (isspace((unsigned char) *str))
    {
        str++;
    }

    return str; // Return the pointer to the trimmed string.
}

char *trimTrailing(const char *str)
{
    /*
        *A function that trims trailing whitespace by leveraging the built-in function isspace(), which checks for:
        *Space (' ').
        *Form feed ('\f').
        *Newline ('\n').
        *Carriage return ('\r').
        *Horizontal tab ('\t').
        *Vertical tab ('\v').
    */

    // Make `end` point to the last element of the string.
    const char *end = str + strlen(str) - 1;

    // Move `end` backwards over trailing whitespace.
    while(end >= str && isspace((unsigned char)*end))
    {
        end--;
    }

    // Calculate the length of the trimmed string.
    size_t trimmed_length = (size_t) (end - str + 1);

    // Allocate memory for the trimmed string and account for the null-terminator.
    char *trimmed = malloc(trimmed_length + 1);
    if(!trimmed)
    {
        throwError("Failed to allocate memory", TRUE);
    }

    // Copy the trimmed string and null-terminate it.
    strncpy(trimmed, str, trimmed_length);
    trimmed[trimmed_length] = '\0';

     // Return the pointer to the trimmed string.
    return trimmed;
}

// Trim both leading and trailing whitespace.
char *trimString(const char *str) 
{
    // Trim leading whitespace.
    const char *leading_trimmed = trimLeading(str);

    // Trim trailing whitespace.
    char *fully_trimmed = trimTrailing(leading_trimmed);

    return fully_trimmed;
}

// TODO: Cleanup after calling trimString and trimTrailing.

// TODO: Implement a log function.

// TODO: Enhance getTime() by making it return time, but be ware of race conditions.

// TODO: Handle buffer flushing in general.