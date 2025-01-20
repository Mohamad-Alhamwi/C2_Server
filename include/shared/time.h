#ifndef TIME_H
#define TIME_H

// Maximum size of the buffer to store formatted date and time strings, including the null terminator.
#define DATE_TIME_BUFFER_SIZE 32

// Format macros.
#define FORMAT_FULL_DATETIME 1
#define FORMAT_TIME          2
#define FORMAT_DATE          3
#define FORMAT_HOUR          4
#define FORMAT_MINUTE        5
#define FORMAT_SECOND        6

void getTime(char *buff, int format);

#endif