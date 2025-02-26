#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <stddef.h>

// Color codes.
#define RESET         "\033[0m"      // Reset to default color.
#define INFORMATIONAL "\033[34m"     // Blue for informational messages.
#define SUCCESSFUL    "\033[32m"     // Green for success messages.
#define ERROR         "\033[31m"     // Red for error messages.
#define WARNING       "\033[33m"     // Yellow for warning messages.

// Log message type's switch.
#define LOG_INFORMATIONAL 0
#define LOG_SUCCESSFUL    1
#define LOG_WARNING       2
#define LOG_ERROR         3

// Log file's name.
#define LOG_FILE "server_logs.txt"

void logTerminal(size_t log_type, const char *log_msg_format, ...);

#endif