#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include "shared/time.h"
#include "shared/utils.h"

// TODO: Enhance getTime() by making it return time, but be ware of race conditions.
void getTime(char *buff, int format)
{
    // Gets the number of seconds and microseconds (since the Epoch).
    struct timeval now;
    gettimeofday(&now, NULL);

    // Gives us a break down of time for our local time zone.
    struct tm *loc_cur_time = localtime(&now.tv_sec);
    
    if(loc_cur_time == NULL)
    {
        // strftime();
        // Gives us the time in string format.
        // Allows us to customize using placeholders.
        // Formats the time into buff.
        snprintf(buff, DATE_TIME_BUFFER_SIZE, WARNING "Uknown Time" RESET);
        return;
    }

    switch(format)
    {
        case FORMAT_FULL_DATETIME: // Full date and time (default).
            snprintf(buff, DATE_TIME_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S.%03ld",
                    loc_cur_time -> tm_year + 1900, loc_cur_time -> tm_mon + 1, loc_cur_time -> tm_mday,
                    loc_cur_time -> tm_hour, loc_cur_time -> tm_min, loc_cur_time -> tm_sec, now.tv_usec / 1000);
            break;
        case FORMAT_TIME: // Just the time.
            snprintf(buff, DATE_TIME_BUFFER_SIZE, "%H:%M:%S.%03ld", loc_cur_time -> tm_hour, loc_cur_time -> tm_min, loc_cur_time -> tm_sec, now.tv_usec / 1000);
            break;
        case FORMAT_DATE: // Just the date.
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%Y-%m-%d", loc_cur_time);
            break;
        case FORMAT_HOUR: // Just the hours.
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%H", loc_cur_time);
            break;
        case FORMAT_MINUTE: // Just the minutes.
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%M", loc_cur_time);
            break;
        case FORMAT_SECOND: // Just the seconds.
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%S", loc_cur_time);
            break;
        case FORMAT_MILLISECOND: // Just the milliseconds.
            snprintf(buff, DATE_TIME_BUFFER_SIZE, "%03ld", now.tv_usec / 1000);
            break;
        default:
            snprintf(buff, DATE_TIME_BUFFER_SIZE, WARNING "Invalid Format" RESET);
            break;
    }

    return;
}