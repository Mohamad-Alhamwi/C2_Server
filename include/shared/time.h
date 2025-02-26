#ifndef TIME_H
#define TIME_H

#include <time.h>
#include <stdint.h>

// Maximum size of the buffer to store formatted date and time strings, including the null terminator.
#define TIMESTAMP_BUFFER_SIZE 32

struct timespec getTime();
uint32_t getNanoseconds(struct timespec now);
uint16_t getMilliseconds(struct timespec now);
void getTimestamp(char *buff);

#endif