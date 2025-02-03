#include <stdio.h>

#include "shared/buffer_manager.h"

// Place it at the start of main() to make sure you get the desired buffering behavior.
void setBufferingMode()
{
    char stdout_buff[STDOUT_BUFF];  // Allocate a buffer for stdout.

    setvbuf(stderr, NULL, _IONBF, 0);  // Disable buffering for stderr.
    setvbuf(stdout, stdout_buff, _IOFBF, STDOUT_BUFF);  // Set stdout to fully-buffered mode.

    return;
}

void initializeBuffer(void * ptr, int value, size_t num)
{
    memset(ptr, value, num);
    return;
}

// Define an alias for initializeBuffer().
void (*zeroBuffer)(void *, int, size_t) = initializeBuffer;