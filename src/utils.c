#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void throwError(const char *custom_err_msg, int should_abort)
{
    /*Handle errors that occur in a system call or library function.*/
    fprintf(stderr, "%s.\n", custom_err_msg);
    fflush(stderr);  // Ensure the custom error message is printed.
    fprintf(stderr, "Error Number: %d.\n", errno);
    fflush(stderr);  // Ensure error number is printed.
    fprintf(stderr, "Error Description: %s.\n", strerror(errno));
    fflush(stderr);  // Ensure error description is printed.

    if(should_abort != 0)
    {
        fprintf(stderr, "Aborted.\n");
        fflush(stderr);  // Ensure the abort message is printed.
        exit(EXIT_FAILURE);
    }

    // TODO: Handle custom errors.
    return;
}
