# ifndef UTILS_H
# define UTILS_H

// Color codes.
# define RESET        "\033[0m"       // Reset to default color.
# define INFORMATIONAL "\033[34m"    // Blue for informational messages.
# define SUCCESSFUL   "\033[32m"     // Green for success messages.
# define ERROR        "\033[31m"     // Red for error messages.

// Boolean-like values for logical operations and flag checks.
# define FALSE 0
# define TRUE 1

// Cleanup operation types for the cleanUp function.
# define CLEANUP_FILE_DESCRIPTORS 1
# define CLEANUP_MEMORY  2

// Buffer size for storing the date and time as a formatted string.
# define DATE_TIME_BUFFER_SIZE 32

# include <stddef.h>

void abortOperation();
void throwError(const char *custom_err_msg, int should_abort);
void cleanUpResources(int cleanup_type, void *resource);
void getTime(char *buff, size_t buff_size);

# endif
