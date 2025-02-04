#ifndef TIME_H
#define TIME_H

// Maximum size of the buffer to store formatted date and time strings, including the null terminator.
#define TIMESTAMP_BUFFER_SIZE 32

// Format macros.
#define FORMAT_FULL_TIMESTAMP 1
#define FORMAT_TIME          2
#define FORMAT_DATE          3
#define FORMAT_HOUR          4
#define FORMAT_MINUTE        5
#define FORMAT_SECOND        6
#define FORMAT_MILLISECOND   7

void getMilliseconds(char *buff, long nanosec);
void getTimestamp(char *buff, int format);

#endif