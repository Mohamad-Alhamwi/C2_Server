#include <stdio.h>
#include <stdarg.h>

#include "shared/time.h"
#include "shared/log_manager.h"

void logTerminal(size_t log_type, const char *log_msg_format, ...)
{
    char time_buff[TIMESTAMP_BUFFER_SIZE];
    getTimestamp(time_buff);

    // Choose the correct output stream.
    FILE *stream = (log_type == LOG_ERROR) ? stderr : stdout;

    va_list var_arg_list;
    va_start(var_arg_list, log_msg_format);

    switch (log_type)
    {
        case LOG_INFORMATIONAL:
            fprintf(stream, "[" INFORMATIONAL "%s" RESET "] " "[" INFORMATIONAL "*" RESET "] ", time_buff);
            break;
        
        case LOG_SUCCESSFUL:
            fprintf(stream, "[" INFORMATIONAL "%s" RESET "] " "[" SUCCESSFUL "+" RESET "] ", time_buff);
            break;

        case LOG_WARNING:
            fprintf(stream, "[" INFORMATIONAL "%s" RESET "] " "[" WARNING "!" RESET "] ", time_buff);
            break;
        
        case LOG_ERROR:
            fprintf(stream, "[" INFORMATIONAL "%s" RESET "] " "[" ERROR "-" RESET "] ", time_buff);
            break;
        
        default:
            fprintf(stream, "[" INFORMATIONAL "%s" RESET "] " "[" WARNING "!" RESET "] " WARNING "Undefined log type! " RESET, time_buff);
            break;
    }

    // Print the formatted message.
    vfprintf(stream, log_msg_format, var_arg_list);
    va_end(var_arg_list);

    // Add newline for readability.
    fprintf(stream, "\n");

    // Ensure immediate output (useful for debugging).
    fflush(stream);
    
    return;
}