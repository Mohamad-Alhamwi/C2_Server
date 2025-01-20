#include <time.h>
#include <stdio.h>

#include "shared/time.h"

void getTime(char *buff, int format)
{
    // Gets the current time in seconds (Number of seconds elapsed since the epoch).
    time_t now = time(NULL);

    // Gives us a break down of time for our local time zone.
    struct tm *loc_cur_time = localtime(&now);
    
    if(loc_cur_time == NULL)
    {
        // TODO: Handle this error.
        // strftime();
        // Gives us the time in string format.
        // Allows us to customize using placeholders.
        // Formats the time into buff.
        snprintf(buff, DATE_TIME_BUFFER_SIZE, "Uknown Time");
        return;
    }

    switch(format)
    {
        case FORMAT_FULL_DATETIME: // Full date and time (default).
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", loc_cur_time);
            break;
        case FORMAT_TIME: // Just the time.
            strftime(buff, DATE_TIME_BUFFER_SIZE, "%H:%M:%S", loc_cur_time);
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
        default:
            snprintf(buff, DATE_TIME_BUFFER_SIZE, "Invalid Format");
            break;
    }

    return;
}