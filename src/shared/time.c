#include <time.h>
#include <stdio.h>
#include <string.h>

#include "shared/time.h"
#include "shared/utils.h"

void getMilliseconds(char *buff, long nanosec)
{
    snprintf(buff + strlen(buff), TIMESTAMP_BUFFER_SIZE - strlen(buff), "%03ld", nanosec / 1000000);
    return;
}

void getTimestamp(char *buff, int format)
{
    // Gets the number of seconds and nanoseconds (since the Epoch).
    struct timespec now;

    // Get the current precise time.
    clock_gettime(CLOCK_REALTIME, &now);

    // Convert seconds to local time.
    struct tm *loc_cur_time = localtime(&now.tv_sec);
    
    if(loc_cur_time == NULL)
    {
        snprintf(buff, TIMESTAMP_BUFFER_SIZE, WARNING "Uknown Timestamp" RESET);
        return;
    }

    switch(format)
    {
        case FORMAT_FULL_TIMESTAMP: // Full date and time (default).
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S.", loc_cur_time);
            // Append milliseconds from nanoseconds.
            getMilliseconds(buff, now.tv_nsec);
            break;
        case FORMAT_TIME: // Just the time.
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%H:%M:%S.", loc_cur_time);
            // Append milliseconds from nanoseconds.
            getMilliseconds(buff, now.tv_nsec);
            break;
        case FORMAT_DATE: // Just the date.
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%Y-%m-%d", loc_cur_time);
            break;
        case FORMAT_HOUR: // Just the hours.
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%H", loc_cur_time);
            break;
        case FORMAT_MINUTE: // Just the minutes.
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%M", loc_cur_time);
            break;
        case FORMAT_SECOND: // Just the seconds.
            strftime(buff, TIMESTAMP_BUFFER_SIZE, "%S", loc_cur_time);
            break;
        case FORMAT_MILLISECOND: // Just the milliseconds.
            getMilliseconds(buff, now.tv_nsec);
            break;
        default:
            snprintf(buff, TIMESTAMP_BUFFER_SIZE, WARNING "Invalid Time Format" RESET);
            break;
    }

    return;
}