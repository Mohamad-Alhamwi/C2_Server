#include <stdio.h>
#include <string.h>

#include "shared/buffer_manager.h"

// Place it at the start of main() to make sure you get the desired buffering behavior.
/**
 * @ TODO: Understand more about buffering behaviour in C before you fire up this function.
 * void setBufferingMode()
 * {
 *    char stdout_buff[STDOUT_BUFF];  // Allocate a buffer for stdout.
 *
 *    setvbuf(stderr, NULL, _IONBF, 0);  // Disable buffering for stderr.
 *    setvbuf(stdout, stdout_buff, _IOFBF, STDOUT_BUFF);  // Set stdout to fully-buffered (block-buffered) mode.
 *
 *    return;
 * }
 */

