#include <time.h>
#include <stdio.h>
#include <string.h>

#include "shared/time.h"
#include "shared/utils.h"
#include "shared/log_manager.h"

struct timespec getTime()
{
    // Gets the number of seconds and nanoseconds (since the Epoch).
    struct timespec now;

    // Get the current precise time.
    clock_gettime(CLOCK_REALTIME, &now);

    return now;
}

uint32_t getNanoseconds(struct timespec now) 
{
    // Return nanoseconds (9 digits).
    return now.tv_nsec;
}

uint16_t getMilliseconds(struct timespec now)
{
    // Get nanoseconds.
    uint32_t nanoseconds = getNanoseconds(now);

    // Return milliseconds (3 digits).
    return nanoseconds / 1000000;
}

void getTimestamp(char *buff)
{
    struct timespec now = getTime();

    // Convert seconds to local time.
    struct tm *loc_cur_time = localtime(&now.tv_sec);
    
    if(loc_cur_time == NULL)
    {
        snprintf(buff, TIMESTAMP_BUFFER_SIZE, WARNING "Uknown Timestamp" RESET);
        return;
    }

    strftime(buff, TIMESTAMP_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S.", loc_cur_time);
    // Append milliseconds.
    snprintf(buff + strlen(buff), TIMESTAMP_BUFFER_SIZE - strlen(buff), "%03hu", getMilliseconds(now));

    return;
}