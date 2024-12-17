#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void throwError(const char *custom_err_msg)
{
    fprintf(stderr, "%s.\n", custom_err_msg);
    fprintf(stderr, "Error Number: %d.\n", errno);
    fprintf(stderr, "Error Description: %s.\n", strerror(errno));
    fprintf(stderr, "Aborted.\n");
    exit(EXIT_FAILURE);
}
